#pragma once

#include <string>

namespace Engine
{

	void loadFile(const char* src, std::string* dest);
	void loadFile(const std::string& src, std::string* dest);
	void saveFile(const char* dest, const std::string& contents);
	void saveFile(const std::string& dest, const std::string& contents);

}