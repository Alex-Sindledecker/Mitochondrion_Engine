#pragma once

#include "Core.h"

#ifdef ENGINE_USE_VULKAN

#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#define RENDER_PIPELINE_INIT_SUCCESS 0
#define RENDER_PIPELINE_INIT_FAILURE -1

namespace Engine
{

	struct RenderPipelineInitStatus
	{
		int code = RENDER_PIPELINE_INIT_SUCCESS;
		const char* string = "Success!";
	};

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() {}

		virtual RenderPipelineInitStatus init(GLFWwindow* window);
		virtual void terminate();
		virtual void clearActiveFramebuffer(BitField flags) = 0;
		virtual void _renderTriangle() = 0;
		virtual void setClearColor(const float r, const float g, const float b) = 0;
		virtual void enableWireframe() {}
		virtual void disableWireframe() {}

	protected:
		GLFWwindow* window;
	};

}