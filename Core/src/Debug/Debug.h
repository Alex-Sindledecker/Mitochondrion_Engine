#pragma once

#include "../Application/Core.h"

namespace Engine
{

	class ENGINE_API LogTarget
	{
	public:
		virtual ~LogTarget() = 0 {};

		virtual const char* getName() = 0;
		virtual LogTarget* getHandle() = 0;
		virtual void logError(const char* msg) = 0;
		virtual void logWarning(const char* msg) = 0;
		virtual void logMessage(const char* msg) = 0;
	};

	class ENGINE_API Debug
	{
	public:
		

	};

}