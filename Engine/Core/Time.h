#pragma once

#include <string>

namespace Time
{

	//Gets the time since the program started
	double getCurrentTime();
	//Stores the current time in dest as MIN:SEC:MIL
	std::string getCurrentTimeString();

}