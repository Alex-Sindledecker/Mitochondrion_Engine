#include "pch.h"
#include "Time.h"
#include "StringTools.h"

namespace Engine
{

	Clock Clock::mGlobalClock;

	Clock::Clock()
	{
		mStart = ENGINE_API_CNOW;
	}

	double Clock::tick()
	{
		auto current = ENGINE_API_CNOW;
		double elapsed = std::chrono::duration<double>(current - mLastTick).count();
		mLastTick = current;

		return elapsed;
	}

	double Clock::now()
	{
		return std::chrono::duration<double>(ENGINE_API_CNOW - mStart).count();
	}

	std::string Clock::nowAsMSM()
	{
		auto elapsed = ENGINE_API_CNOW - mStart;
		int min = std::chrono::duration_cast<Minutes>(elapsed).count();
		int sec = std::chrono::duration_cast<Seconds>(elapsed).count();
		int mil = std::chrono::duration_cast<Milliseconds>(elapsed).count();

		return buildFormattedString("[{}:{}:{}]", min, sec % 60, mil % 1000);
	}

	void Clock::restart()
	{
		mStart = ENGINE_API_CNOW;
	}

	double Clock::getGlobalTime()
	{
		return mGlobalClock.now();
	}

	std::string Clock::getGlobalTimeAsMSM()
	{
		return mGlobalClock.nowAsMSM();
	}

}