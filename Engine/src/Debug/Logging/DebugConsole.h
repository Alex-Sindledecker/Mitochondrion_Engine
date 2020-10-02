#pragma once

#include "Debug/Debug.h"

namespace Engine
{

	class DebugConsole : public LogTarget
	{
	public:
		virtual void logError(const char* msg) override;
		virtual void logWarning(const char* msg) override;
		virtual void logMessage(const char* msg) override;

		static DebugConsole& getInstance();

		DebugConsole(const DebugConsole&) = delete;
		void operator=(const DebugConsole&) = delete;

	private:
		DebugConsole() {}
		~DebugConsole() {}

		static void log(const char* msg, u8 color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		static void setTextColor(int color);
	};

}