#include "pch.h"
#include "App.h"

#include "GLFW/glfw3.h"

namespace Engine
{

	App::App()
	{
		glfwInit();
	}

	App::~App()
	{
		glfwTerminate();
	}

	void App::run()
	{
	}

}