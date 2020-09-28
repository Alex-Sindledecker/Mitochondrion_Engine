#include "pch.h"
#include "Time.h"
#include "StringTools.h"

namespace Engine
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
		double nan = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() % 1000000;

		return buildFormattedString("[{}m:{}s:{}ms]", min, sec % 60, nan / (double)1000000);
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

}