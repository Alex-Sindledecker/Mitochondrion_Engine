#include "mepch.h"
#include "Time.h"
#include "StringTools.h"

namespace mito
{

	Clock Clock::mGlobalClock;

	Clock::Clock()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	double Clock::tick()
	{
		auto current = std::chrono::high_resolution_clock::now();
		double elapsed = std::chrono::duration<double>(current - lastTick).count();
		lastTick = current;

		return elapsed;
	}

	double Clock::now()
	{
		return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
	}

	std::string Clock::nowAsMSM()
	{
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		int min = std::chrono::duration_cast<Minutes>(elapsed).count();
		int sec = std::chrono::duration_cast<Seconds>(elapsed).count();
		double mil = std::chrono::duration_cast<Nanoseconds>(elapsed).count() / 1000000.0;

		return buildFormattedString("[{}m:{}s:{}ms]", min, sec % 60, fmod(mil, 1000.0));
	}

	void Clock::restart()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	double Clock::getGlobalTime()
	{
		return mGlobalClock.now();
	}

	std::string Clock::getGlobalTimeAsMSM()
	{
		return mGlobalClock.nowAsMSM();
	}

	Timer::Timer()
	{
	}

	void Timer::start()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	double Timer::stop()
	{
		return std::chrono::duration_cast<Nanoseconds>(std::chrono::high_resolution_clock::now() - startTime).count() / 1000000.0;
	}

	void MITO_API sleepFor(double seconds)
	{
		std::this_thread::sleep_for(Milliseconds(static_cast<int>(seconds * 1000)));
	}

}