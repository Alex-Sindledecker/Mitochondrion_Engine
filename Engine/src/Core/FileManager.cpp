#include "pch.h"
#include "FileManager.h"

#include "Debug/Debug.h"

namespace Engine
{

	void Engine::loadFile(const char* src, std::string* dest)
	{
		std::ifstream file(src);

		if (!file.is_open())
		{
			Debug::logError("Could not open file: {}!", src);
			dest->assign("");
			file.close();
			return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			dest->append(line);
		}
			
		file.close();
	}

	void loadFile(const std::string& src, std::string* dest)
	{
		loadFile(src.c_str(), dest);
	}

	void saveFile(const char* dest, const std::string& contents)
	{
		std::ofstream file(dest);

		if (!file.is_open())
		{
			Debug::logError("There was an error when attempting to save to {}!", dest);
			return;
		}
		
		file.write(contents.c_str(), contents.length());
		file.close();
	}

	void saveFile(const std::string& dest, const std::string& contents)
	{
		saveFile(dest.c_str(), contents);
	}

}
