#include "pch.h"
#include "LogTarget.h"

namespace Engine
{

	void EmptyLogTarget::logError(const char* msg) {}

	void EmptyLogTarget::logWarning(const char* msg) {}

	void EmptyLogTarget::logMessage(const char* msg) {}

}