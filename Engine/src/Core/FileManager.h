#pragma once

#include "Core.h"
#include "Debug/Debug.h"

#include <filesystem>

namespace Engine
{

	static void testThingy()
	{
		std::string path = "C:/";
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			
		}
	}

	class FileManager
	{
	public:

	private:

	};

}