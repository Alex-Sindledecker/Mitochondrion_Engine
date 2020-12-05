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
			std::cout << "[" << time << "]   ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::WRN:
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << "[" << time << "] ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::MSG:
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
			std::cout << "[" << time << "] ----> " << message << std::endl;
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
			output << "[" << time << "]   ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::WRN:
			output << "[" << time << "] ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::MSG:
			output << "[" << time << "] ----> " << message << std::endl;
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
			file << "[" << time << "]   ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::WRN:
			file << "[" << time << "] ----> " << message << std::endl;
			break;
		case EngineDebugger::LogType::MSG:
			file << "[" << time << "] ----> " << message << std::endl;
			break;
		}
	}

	static std::stack<ProfilingSession> sessions;
	static std::stack<const char*> activeProfiles;

	void beginProfilingSession(const char* name)
	{
		sessions.push({ name, {}, util::getCurrentTime() });
	}

	ProfilingSession endProfilingSession()
	{
		ProfilingSession session = std::move(sessions.top());
		session.duration = util::getCurrentTime() - session.duration;
		sessions.pop();
		return session;
	}

	void beginProfile(const char* name)
	{
		ProfilingSession& session = sessions.top();
		session.profiles[name] = util::getCurrentTime();
		activeProfiles.push(name);
	}

	void endProfile()
	{
		ProfilingSession& session = sessions.top();
		const char* activeProfile = activeProfiles.top();
		session.profiles[activeProfile] = util::getCurrentTime() - session.profiles[activeProfile];
		activeProfiles.pop();
	}

	void printProfilingSession(ProfilingSession& session)
	{
		static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);

		std::cout << util::formatString("Profiling session for \"{}\" lasted {} seconds. {} sections were tested:", session.name, session.duration, session.profiles.size()) << std::endl;
		for (const auto& profile : session.profiles)
		{
			std::cout << util::formatString("\"{}\": {} seconds ({}%)", profile.first, profile.second, profile.second / session.duration) << std::endl;
		}
		std::cout << std::endl;

		SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

}