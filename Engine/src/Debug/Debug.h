#pragma once

#include "DebugTools.h"
#include "Logging/LogTarget.h"
#include "Core/StringTools.h"
#include "Core/Time.h"

#include <mutex>

namespace Engine
{

	class Debug
	{
	public:
		using LogLevel = u8;
		const static int LOG_ALL = 0b0111;
		const static int LOG_ERROR = 0b0001;
		const static int LOG_WARNING = 0b0010;
		const static int LOG_MESSAGE = 0b0100;

	public:
		static void init();
		static void terminate();

		static void setLogTarget(LogTarget* handle);
		static void setLogLevel(LogLevel level);

		template<class... Ts>
		static void logError(std::string error, Ts... args)
		{
			if (target != nullptr)
			{
				std::lock_guard<std::mutex> lk(atomicLogMutex);

				if (level & LOG_ERROR)
				{
					std::string time = Clock::getGlobalTimeAsMSM();
					target->logError(buildFormattedString(time + "(ERROR!) -> " + error, args...).c_str());
				}
			}
		}

		template<class... Ts>
		static void logWarning(std::string warning, Ts... args)
		{
			if (target != nullptr)
			{
				std::lock_guard<std::mutex> lk(atomicLogMutex);

				if (level & LOG_WARNING)
				{
					std::string time = Clock::getGlobalTimeAsMSM();
					target->logWarning(buildFormattedString(time + "(WARNING!) -> " + warning, args...).c_str());
				}
			}
		}

		template<class... Ts>
		static void logMessage(std::string message, Ts... args)
		{
			if (target != nullptr)
			{
				std::lock_guard<std::mutex> lk(atomicLogMutex);

				if (level & LOG_MESSAGE)
				{
					std::string time = Clock::getGlobalTimeAsMSM();
					target->logMessage(buildFormattedString(time + "(MESSAGE) -> " + message, args...).c_str());
				}
			}
		}

		static void logError(std::string error);
		static void logWarning(std::string warning);
		static void logMessage(std::string message);

		Debug(const Debug&) = delete;
		void operator=(const Debug&) = delete;

	private:
		Debug();
		~Debug() {}

		static LogTarget* target;
		static LogLevel level;
		static std::mutex atomicLogMutex;
	};

}