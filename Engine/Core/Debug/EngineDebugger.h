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

#define PROFILE(function, ...) EngineDebugger::beginProfile(#function); function(__VA_ARGS__); EngineDebugger::endProfile()

namespace EngineDebugger
{
	struct ProfilingSession
	{
		std::unordered_map<const char*, double> profiles;
		double duration;
	};
	enum class LogType { ERR, WRN, MSG };

	void dumpMemoryLeaks();
	void log(const std::string& message, LogType type = LogType::MSG);
	void flog(const char* file, const std::string& message, LogType type = LogType::MSG);
	void flog(std::ofstream& file, const std::string& message, LogType type = LogType::MSG);
	void beginProfilingSession();
	ProfilingSession endProfilingSession();
	void beginProfile(const char* name);
	void endProfile();
	void printProfilingSession(ProfilingSession& session);
};

