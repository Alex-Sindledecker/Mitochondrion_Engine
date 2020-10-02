#include "pch.h"

#include "Debug.h"
#include "Logging/DebugConsole.h"

namespace Engine
{

	LogTarget* Debug::target;
	Debug::LogLevel Debug::level;
	std::mutex Debug::atomicLogMutex;

	void Debug::init()
	{
		target = &DebugConsole::getInstance();
		level = LOG_ALL;
	}

	void Debug::setLogTarget(LogTarget* handle)
	{
		target = handle;
	}

	void Debug::setLogLevel(LogLevel level)
	{
		level = level;
	}

	void Debug::logError(std::string error)
	{
		if (target != nullptr)
		{
			std::lock_guard<std::mutex> lk(atomicLogMutex);

			if (level & LOG_ERROR)
			{
				std::string time = Clock::getGlobalTimeAsMSM();
				target->logError((time + "(ERROR!) -> " + error).c_str());
			}
		}
	}

	void Debug::logWarning(std::string warning)
	{
		if (target != nullptr)
		{
			std::lock_guard<std::mutex> lk(atomicLogMutex);

			if (level & LOG_WARNING)
			{
				std::string time = Clock::getGlobalTimeAsMSM();
				target->logWarning((time + "(WARNING!) -> " + warning).c_str());
			}
		}
	}

	void Debug::logMessage(std::string message)
	{
		if (target != nullptr)
		{
			std::lock_guard<std::mutex> lk(atomicLogMutex);

			if (level & LOG_MESSAGE)
			{
				std::string time = Clock::getGlobalTimeAsMSM();
				target->logMessage((time + "(MESSAGE) -> " + message).c_str());
			}
		}
	}
}