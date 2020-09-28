#include "pch.h"
#include "Debug.h"
#include "Logging/DebugConsole.h"

namespace Engine
{

	std::mutex DebugLogger::atomicLogMutex;

	DebugLogger& DebugLogger::getInstance()
	{
		static DebugLogger debug;
		return debug;
	}

	void DebugLogger::setTarget(LogTarget* handle)
	{
		if (handle == nullptr)
			target = &EmptyLogger;
		else
			target = handle;
	}

	void DebugLogger::setLevel(LogLevel level)
	{
		level = level;
	}

	void DebugLogger::logError(std::string error)
	{
		std::lock_guard<std::mutex> lk(atomicLogMutex);

		if (level & LOG_ERROR)
		{
			std::string time = Clock::getGlobalTimeAsMSM();
			target->logError((time + "(ERROR!) -> " + error).c_str());
		}
	}

	void DebugLogger::logWarning(std::string warning)
	{
		std::lock_guard<std::mutex> lk(atomicLogMutex);

		if (level & LOG_WARNING)
		{
			std::string time = Clock::getGlobalTimeAsMSM();
			target->logWarning((time + "(WARNING!) -> " + warning).c_str());
		}
	}

	void DebugLogger::logMessage(std::string message)
	{
		std::lock_guard<std::mutex> lk(atomicLogMutex);

		if (level & LOG_MESSAGE)
		{
			std::string time = Clock::getGlobalTimeAsMSM();
			target->logMessage((time + "(MESSAGE) -> " + message).c_str());
		}
	}

	DebugLogger::DebugLogger()
	{
		target = &DebugConsole::getInstance();
		level = LOG_ALL;
	}
}