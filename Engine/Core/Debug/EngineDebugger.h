#pragma once

#ifdef _DEBUG

#ifndef DBG_ALLOC_TRACK_POOL_SIZE
#define DBG_ALLOC_TRACK_POOL_SIZE 2048
#endif

#include <array>

void* operator new(size_t size, const char* file, int line);
void operator delete(void* mem);

#define NEW new(__FILE__, __LINE__)

#else

#define NEW new

#endif

namespace EngineDebugger
{
	enum class LogType { ERR, WRN, MSG };

	void dumpMemoryLeaks();
	void log(const std::string& message, LogType type = LogType::MSG);
};

