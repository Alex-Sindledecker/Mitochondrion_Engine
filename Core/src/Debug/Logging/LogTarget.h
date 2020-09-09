#pragma once

#include "Core/Core.h"

namespace Engine
{

	class ENGINE_API LogTarget
	{
	public:
		virtual ~LogTarget() = 0 {};

		virtual const char* getName() = 0;
		virtual LogTarget* getHandle() = 0;
		virtual void logError(const char* msg, bool lf = true) = 0;
		virtual void logWarning(const char* msg, bool lf = true) = 0;
		virtual void logMessage(const char* msg, bool lf = true) = 0;
	};

	class ENGINE_API EmptyLogTarget : public LogTarget
	{
	public:
		virtual const char* getName() override;
		virtual LogTarget* getHandle() override;
		virtual void logError(const char* msg, bool lf = true) override;
		virtual void logWarning(const char* msg, bool lf = true) override;
		virtual void logMessage(const char* msg, bool lf = true) override;
	} static EmptyLogger;

}