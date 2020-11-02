#include "mepch.h"
#include "GLCore.h"

#include <GLFW/glfw3.h>

namespace mito::gl
{

	void init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to instantiate GL instance!");
		std::cout << "GL Instantiated!" << std::endl;
	}

	void terminate()
	{
		
	}

	const OpenGLVersion MITO_API getGLVersion()
	{
		return { 4, 1, "#version 410 core" };
	}

}