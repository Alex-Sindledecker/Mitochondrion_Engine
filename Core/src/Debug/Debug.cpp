#include "pch.h"
#include "Debug.h"
#include "Logging/DebugConsole.h"

namespace Engine
{

	DebugLogger& DebugLogger::getInstance()
	{
		static DebugLogger debug;
		return debug;
	}

	void DebugLogger::setTarget(LogTarget* handle)
	{
		if (handle == nullptr)
			mLogTarget = &EmptyLogger;
		else
			mLogTarget = handle;
	}

	void DebugLogger::setLevel(LogLevel level)
	{
		mLogLevel = level;
	}

	DebugLogger::DebugLogger()
	{
		mLogTarget = &DebugConsole::getInstance();
		mLogLevel = LOG_ALL;
	}
}