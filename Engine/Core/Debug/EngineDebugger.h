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

#define DBG_PROFILE1(func, ...) EngineDebugger::beginProfile(#func); func(__VA_ARGS__); EngineDebugger::endProfile();
#define DBG_PROFILE2(returnVal, func, ...)  EngineDebugger::beginProfile(#func); returnVal = func(__VA_ARGS__); EngineDebugger::endProfile();

namespace EngineDebugger
{
	struct ProfilingSession
	{
		const char* name;
		std::unordered_map<const char*, double> profiles;
		double duration;
	};
	enum class LogType { ERR, WRN, MSG };

	void dumpMemoryLeaks();
	void log(const std::string& message, LogType type = LogType::MSG);
	void flog(const char* file, const std::string& message, LogType type = LogType::MSG);
	void flog(std::ofstream& file, const std::string& message, LogType type = LogType::MSG);
	void beginProfilingSession(const char* name);
	ProfilingSession endProfilingSession();
	void beginProfile(const char* name);
	void endProfile();
	void printProfilingSession(ProfilingSession& session);
};

