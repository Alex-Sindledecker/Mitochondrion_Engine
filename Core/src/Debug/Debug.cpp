#include "Debug.h"
#include "DebugConsole.h"

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
		mLogTarget = DebugConsole::getInstance().getHandle();
		mLogLevel = LOG_ALL;
	}

	const char* EmptyLogTarget::getName()
	{
		return nullptr;
	}

	LogTarget* EmptyLogTarget::getHandle()
	{
		return nullptr;
	}

	void EmptyLogTarget::logError(const char* msg, bool lf) {}

	void EmptyLogTarget::logWarning(const char* msg, bool lf) {}

	void EmptyLogTarget::logMessage(const char* msg, bool lf) {}
}