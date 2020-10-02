#pragma once

#include "Core.h"

namespace Engine
{

	class LogTarget
	{
	public:
		virtual ~LogTarget() = 0 {};

		virtual void logError(const char* msg) = 0;
		virtual void logWarning(const char* msg) = 0;
		virtual void logMessage(const char* msg) = 0;
	};

}