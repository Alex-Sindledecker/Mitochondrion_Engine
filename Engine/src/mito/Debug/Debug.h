#pragma once

#include "Core/MitchondiraAPI.h"
#include "Core/Time.h"
#include "Core/StringTools.h"
#include "LogTarget.h"

#include <mutex>

namespace mito
{

	class MITO_API Debug
	{
	public:
		static const u8_t MSG_LOG = 0x01;
		static const u8_t WRN_LOG = 0x02;
		static const u8_t ERR_LOG = 0x04;
		static const u8_t ALL_LOG = 0x07;
	public:
		static void init();
		static void terminate();

		template<class... Ts>
		static void log(const u8_t type, const std::string& message, Ts... args)
		{
			static std::mutex logMutex; //Logging needs to be an atomic operation to ensure that multiple logs don't overlap

			std::lock_guard<std::mutex> lk(logMutex);

			std::string time = std::move(Clock::getGlobalTimeAsMSM());
			if (logLevel & type == MSG_LOG)
			{
				logTarget->logMessage(buildFormattedString(time + "(MESSAGE!) -> " + message, args...).c_str());
			}
			if (logLevel & type == WRN_LOG)
			{
				logTarget->logWarning(buildFormattedString(time + "(WARNING!) -> " + message, args...).c_str());
			}
			if (logLevel & type == ERR_LOG)
			{
				logTarget->logError(buildFormattedString(time + "(ERROR!) -> " + message, args...).c_str());
			}
		}

	private:
		static u8_t logLevel;
		static LogTarget* logTarget;
	};

}