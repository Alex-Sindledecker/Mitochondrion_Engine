#pragma once

#include "mito/Core/MitochondriaAPI.h"

namespace mito
{

	class MITO_API LogTarget
	{
	public:
		virtual ~LogTarget() = 0 {};

		virtual void logError(const char* msg) = 0;
		virtual void logWarning(const char* msg) = 0;
		virtual void logMessage(const char* msg) = 0;
	};

}