#include "pch.h"
#include "LogTarget.h"

namespace Engine
{

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