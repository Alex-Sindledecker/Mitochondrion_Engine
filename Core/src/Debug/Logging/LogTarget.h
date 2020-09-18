#pragma once

#include "Core/Core.h"

namespace Engine
{

	class ENGINE_API LogTarget
	{
	public:
		virtual ~LogTarget() = 0 {};

		virtual void logError(const char* msg) = 0;
		virtual void logWarning(const char* msg) = 0;
		virtual void logMessage(const char* msg) = 0;
	};

	class ENGINE_API EmptyLogTarget : public LogTarget
	{
	public:
		virtual void logError(const char* msg) override;
		virtual void logWarning(const char* msg) override;
		virtual void logMessage(const char* msg) override;
	} static EmptyLogger;

}