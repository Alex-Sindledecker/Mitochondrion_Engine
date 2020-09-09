#pragma once

#include "Core.h"

#include <string>
#include <sstream>
#include <iomanip>

namespace Engine
{

	static void _buildFormattedString(std::stringstream& ss, std::string& string, int offset)
	{
		if (ss.str().length() == 0)
			ss << string;
		else
		{
			ss << string.substr(offset);
		}
	}

	template<class T, class... Ts>
	static void _buildFormattedString(std::stringstream& ss, std::string& string, int offset, T arg, Ts... args)
	{
		auto start = string.find("{", offset);
		if (start != std::string::npos)
		{
			auto end = string.find("}", start);

			ss << string.substr(offset, start - offset) << arg;
			_buildFormattedString(ss, string, end + 1, args...);
		}
		else
		{
			ss << arg;
			_buildFormattedString(ss, string, offset, args...);
		}
	}

	template<class... Ts>
	static std::string buildFormattedString(std::string string, Ts... args)
	{
		std::stringstream ss;
		_buildFormattedString(ss, string, 0, args...);
		return ss.str();
	}

}