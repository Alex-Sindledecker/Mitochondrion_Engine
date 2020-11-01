#pragma once

#include "mito/Debug/Debug.h"

namespace mito
{

	class MITO_API ConsoleLogger : public LogTarget
	{
	public:
		virtual void logError(const char* msg) override;
		virtual void logWarning(const char* msg) override;
		virtual void logMessage(const char* msg) override;

		static ConsoleLogger& getInstance();

		ConsoleLogger(const ConsoleLogger&) = delete;
		void operator=(const ConsoleLogger&) = delete;

	private:
		ConsoleLogger() {}
		~ConsoleLogger() {}

		static void log(const char* msg, u8_t color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		static void setTextColor(int color);
	};

}