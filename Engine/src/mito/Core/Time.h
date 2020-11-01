#pragma once

#include "mito/Core/MitochondriaAPI.h"

#include <string>
#include <chrono>

namespace mito
{
	using Minutes = std::chrono::minutes;
	using Seconds = std::chrono::seconds;
	using Milliseconds = std::chrono::milliseconds;
	using Microseconds = std::chrono::microseconds;
	using Nanoseconds = std::chrono::nanoseconds;
	using TimeStamp = std::chrono::high_resolution_clock::time_point;

	class MITO_API Clock
	{
	public:
		Clock();

		//Updates the clocks time and returns the time since the last tick
		double tick();
		//Returns the time since creation or the last restart
		double now();

		template<class T>
		double now()
		{
			static_assert(std::is_same<T, std::chrono::duration>::value, "Invalid time value passed!");
			return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - start).count();
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
		TimeStamp start;
		TimeStamp lastTick;

		static Clock mGlobalClock;
	};

	class MITO_API Timer
	{
	public:
		Timer();

		//Starts the timer
		void start();
		//Stops the timer and returns the elapsed time in milliseconds
		double stop();

	private:
		TimeStamp startTime;
	};

	void MITO_API sleepFor(double seconds);
}