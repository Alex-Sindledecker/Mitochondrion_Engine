#include "App.h"

#include <iostream>

namespace Engine
{

	App::App()
	{
	}

	App::~App()
	{
	}

	void App::print(const char* str, int line, const char* file)
	{
		std::cout << str << " " << line << " " << file << std::endl;
	}

	void App::run()
	{
	}

}