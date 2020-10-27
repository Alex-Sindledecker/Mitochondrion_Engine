#include "mepch.h"
#include "Debug.h"
#include "ConsoleLogger.h"

namespace mito
{

	u8_t Debug::logLevel = ALL_LOG;
	LogTarget* Debug::logTarget;

	void Debug::init()
	{
		logLevel = ALL_LOG;
		logTarget = &ConsoleLogger::getInstance();
	}

	void Debug::terminate()
	{

	}

}