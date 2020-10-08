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

}
