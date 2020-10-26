#pragma once

#include "MitchondiraAPI.h"

#include <string>
#include <sstream>
#include <iomanip>

namespace mito
{

	static void buildFormattedString(std::stringstream& ss, std::string& string, int offset)
	{
		if (ss.str().length() == 0)
			ss << string;
		else
		{
			ss << string.substr(offset);
		}
	}

	template<class T, class... Ts>
	static void buildFormattedString(std::stringstream& ss, std::string& string, int offset, T arg, Ts... args)
	{
		size_t bracketPos = string.find('{', offset);
		if (bracketPos != std::string::npos)
		{
			ss << string.substr(offset, bracketPos - offset);
			if (string[bracketPos + 1] == '}')
			{
				ss << arg;
				buildFormattedString(ss, string, bracketPos + 2, args...);
			}
			else
			{
				ss << '{';
				buildFormattedString(ss, string, bracketPos + 1, arg, args...);
			}
		}
		else
			ss << string.substr(offset);
	}

	template<class... Ts>
	static std::string buildFormattedString(std::string string, Ts... args)
	{
		std::stringstream ss;
		buildFormattedString(ss, string, 0, args...);
		return ss.str();
	}

}