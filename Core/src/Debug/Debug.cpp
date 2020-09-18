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
			target = &EmptyLogger;
		else
			target = handle;
	}

	void DebugLogger::setLevel(LogLevel level)
	{
		level = level;
	}

	DebugLogger::DebugLogger()
	{
		target = &DebugConsole::getInstance();
		level = LOG_ALL;
	}
}