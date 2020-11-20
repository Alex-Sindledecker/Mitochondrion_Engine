#pragma once

#include <string>

namespace Time
{

	//Gets the time since the program started
	double getElapsedTime();
	//Stores the current time in dest as MIN:SEC:MIL
	std::string getCurrentTimeString();

}