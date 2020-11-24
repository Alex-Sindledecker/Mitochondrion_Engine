#include "mepch.h"
#include "EngineDebugger.h"
#include "Core/Utilities.h"

#include <Windows.h>

#ifdef _DEBUG

struct __DBG_MemAllocationInfo
{
	const char* file;
	int line;
};

static std::array<__DBG_MemAllocationInfo, DBG_ALLOC_TRACK_POOL_SIZE> allocInfos;
static std::array<void*, DBG_ALLOC_TRACK_POOL_SIZE> allocs;
static unsigned int allocIndex = 0;

void* operator new(size_t size, const char* file, int line)
{
	void* mem = malloc(size);
	allocs[allocIndex] = mem;
	allocInfos[allocIndex] = { file, line };
	allocIndex++;

	return mem;
}

void operator delete(void* mem)
{
	free(mem);
	*reinterpret_cast<unsigned char*>(mem) = 0xcc;
}

#else



#endif

namespace EngineDebugger
{

	void dumpMemoryLeaks()
	{
#ifdef _DEBUG
		for (int i = 0; i < allocIndex; i++)
		{
			if (*reinterpret_cast<unsigned char*>(allocs[i]) != 0xcc)
			{
				std::cout << "Memory Leak Detected! Address : " << allocs[i] << "\nFile: " << allocInfos[i].file << ", Line: " << allocInfos[i].line << '\n';
			}
		}
#else
		EngineDebugger::log("The build is not currently configured for memory leak detection!", EngineDebugger::LogType::WRN);
#endif
	}

	void log(const std::string& message, LogType type)
	{
#ifdef _DEBUG
		static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		std::string time = util::getCurrentTimeString();

		switch (type)
		{
		case EngineDebugger::LogType::ERR:
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
			std::cout << "ERROR! (" << time << ")   ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::WRN:
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << "WARNING! (" << time << ") ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::MSG:
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
			std::cout << "MESSAGE (" << time << ") ----> " << message << std::endl;
			break;
		}

		SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else

#endif
	}

	void flog(const char* file, const std::string& message, LogType type)
	{
		std::ofstream output(file, std::ios::app);
		if (!output.is_open())
		{
			log(util::formatString("Failed to open file {} for logging!", file), LogType::WRN);
			return;
		}

		std::string time = util::getCurrentTimeString();

		switch (type)
		{
		case EngineDebugger::LogType::ERR:
			output << "ERROR! (" << time << ")   ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::WRN:
			output << "WARNING! (" << time << ") ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::MSG:
			output << "MESSAGE (" << time << ") ----> " << message << std::endl;
			break;
		}

		output.close();
	}

	void flog(std::ofstream& file, const std::string& message, LogType type)
	{
		std::string time = util::getCurrentTimeString();

		switch (type)
		{
		case EngineDebugger::LogType::ERR:
			file << "ERROR! (" << time << ")   ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::WRN:
			file << "WARNING! (" << time << ") ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::MSG:
			file << "MESSAGE (" << time << ") ----> " << message << std::endl;
			break;
		}
	}

	static std::queue<ProfilingSession> sessions;
	static const char* activeProfile;

	void beginProfilingSession()
	{
		sessions.push({});
		sessions.front().duration = util::getCurrentTime();
	}

	ProfilingSession endProfilingSession()
	{
		ProfilingSession session = std::move(sessions.front());
		session.duration = util::getCurrentTime() - session.duration;
		sessions.pop();
		return session;
	}

	void beginProfile(const char* name)
	{
		ProfilingSession& session = sessions.front();
		session.profiles[name] = util::getCurrentTime();
		activeProfile = name;
	}

	void endProfile()
	{
		ProfilingSession& session = sessions.front();
		session.profiles[activeProfile] = util::getCurrentTime() - session.profiles[activeProfile];
	}

	void printProfilingSession(ProfilingSession& session)
	{
		std::cout << util::formatString("Profiling session lasted {} seconds. {} sections were tested:", session.duration, session.profiles.size()) << std::endl;
		for (const auto& profile : session.profiles)
		{
			std::cout << util::formatString("\"{}\": {} seconds ({}%)", profile.first, profile.second, profile.second / session.duration) << std::endl;
		}
	}

}