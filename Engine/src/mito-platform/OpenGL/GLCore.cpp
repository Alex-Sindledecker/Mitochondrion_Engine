#include "mepch.h"
#include "GLCore.h"

namespace mito::gl
{

	void init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to instantiate GL instance!");
	}

	void terminate()
	{
		
	}

}