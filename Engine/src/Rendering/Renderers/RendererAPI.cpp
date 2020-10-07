#include "pch.h"
#include "RendererAPI.h"

namespace Engine
{
	RenderPipelineInitStatus RendererAPI::init(GLFWwindow* window)
	{
		this->window = window;
		return RenderPipelineInitStatus();
	}

	void RendererAPI::terminate()
	{
	}

}
