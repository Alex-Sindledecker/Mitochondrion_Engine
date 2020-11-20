#include "mepch.h"
#include "EngineDebugger.h"
#include "Core/Time.h"

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

void EngineDebugger::dumpMemoryLeaks()
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
	//TODO: Warning, "The build is not currently configured for memory leak detection"
#endif
}

void EngineDebugger::log(const std::string& message, LogType type)
{
#ifdef _DEBUG
	static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	std::string time = Time::getCurrentTimeString();

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
