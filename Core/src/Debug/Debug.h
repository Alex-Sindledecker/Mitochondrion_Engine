#pragma once

#include "Logging/LogTarget.h"
#include "Core/StringTools.h"
#include "Core/Time.h"

namespace Engine
{

	class ENGINE_API DebugLogger
	{
	public:
		using LogLevel = int;
		const int LOG_ALL = 0b0111;
		const int LOG_ERROR = 0b0001;
		const int LOG_WARNING = 0b0010;
		const int LOG_MESSAGE = 0b0100;

	public:
		static DebugLogger& getInstance();

		void setTarget(LogTarget* handle);
		void setLevel(LogLevel level);

		template<class... Ts>
		void logError(std::string error, Ts... args)
		{
			if (mLogLevel & LOG_ERROR)
			{
				std::string time = clock.nowAsMSM();
				mLogTarget->logError(buildFormattedString(time + "(ERROR!) -> " + error, args...).c_str());
			}
		}

		template<class... Ts>
		void logWarning(std::string warning, Ts... args)
		{
			if (mLogLevel & LOG_WARNING)
			{
				std::string time = clock.nowAsMSM();
				mLogTarget->logWarning(buildFormattedString(time + "(WARNING!) -> " + warning, args...).c_str());
			}
		}

		template<class... Ts>
		void logMessage(std::string message, Ts... args)
		{
			if (mLogLevel & LOG_MESSAGE)
			{
				std::string time = clock.nowAsMSM();
				mLogTarget->logMessage(buildFormattedString(time + "(MESSAGE) -> " + message, args...).c_str());
			}
		}

		DebugLogger(const DebugLogger&) = delete;
		void operator=(const DebugLogger&) = delete;

	private:
		DebugLogger();
		~DebugLogger() {}

		LogTarget* mLogTarget;
		LogLevel mLogLevel;
		Clock clock;
	};

}