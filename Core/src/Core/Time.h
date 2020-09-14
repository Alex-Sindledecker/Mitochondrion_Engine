#pragma once

#include "Core.h"

#include <string>
#include <chrono>

#define ENGINE_API_CNOW std::chrono::high_resolution_clock::now()

namespace Engine
{
	class ENGINE_API Clock
	{
	public:
		using Minutes = std::chrono::minutes;
		using Seconds = std::chrono::seconds;
		using Milliseconds = std::chrono::milliseconds;
		using TimeStamp = std::chrono::high_resolution_clock::time_point;
	public:
		Clock();

		//Updates the clocks time and returns the time since the last tick
		double tick();
		//Returns the time since creation or the last restart
		double now();

		template<class T>
		double now()
		{
			static_assert(std::is_same<T, Minutes>::value || std::is_same<T, Seconds>::value || std::is_same<T, Milliseconds>::value, "Invalid time value passed!");
			return std::chrono::duration_cast<T>(ENGINE_API_CNOW - mStart).count();
		}
		//Returns the time since creation or the last restart in "[minutes:seconds:milliseconds]" format
		std::string nowAsMSM();
		//Resets the start time to the current global time
		void restart();

		//Returns the time since the program start in seconds
		static double getGlobalTime();
		//Returns the time since program start in "[minutes:seconds:milliseconds]" format
		static std::string getGlobalTimeAsMSM();

	private:
		TimeStamp mStart;
		TimeStamp mLastTick;

		static Clock mGlobalClock;
	};
}