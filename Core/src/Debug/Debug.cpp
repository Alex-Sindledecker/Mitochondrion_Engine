#include "Debug.h"
#include "DebugConsole.h"

namespace Engine
{

	Debug& Debug::getInstance()
	{
		static Debug debug;
		return debug;
	}

	void Debug::setLogTarget(LogTarget* handle)
	{
		mLogTarget = handle;
	}

	void Debug::setLogLevel(LogLevel level)
	{
		mLogLevel = level;
	}

	Debug::Debug()
	{
		mLogTarget = DebugConsole::getInstance().getHandle();
		mLogLevel = LOG_ALL;
	}

}