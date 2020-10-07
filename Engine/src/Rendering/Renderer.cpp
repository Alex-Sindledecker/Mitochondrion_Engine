#include "pch.h"

#include "Renderer.h"

namespace Engine
{

	GLFWwindow* Renderer::windowPtr;
	RendererAPI* Renderer::renderAPI;

	RenderPipelineInitStatus Renderer::init(GLFWwindow* windowPtr)
	{
		Renderer::windowPtr = windowPtr;

		#ifdef ENGINE_USE_VULKAN
			renderAPI = new VulkanRenderer();
		#else
			renderAPI = new OpenGLRenderer();
		#endif

		return renderAPI->init(windowPtr);
	}

	void Renderer::terminate()
	{
		renderAPI->terminate();
		delete renderAPI;
	}

	void Renderer::clearActiveFramebuffer(BitField flags)
	{
		renderAPI->clearActiveFramebuffer(flags);
	}

	void Renderer::setNormalizedClearColorRGB(const float r, const float g, const float b)
	{
		renderAPI->setClearColor(r, g, b);
	}

	void Renderer::setClearColorRGB(const u8_t r, const u8_t g, const u8_t b)
	{
		renderAPI->setClearColor(r / 255.f, g / 255.f, b / 255.f);
	}

	void Renderer::_renderTriangle()
	{
		renderAPI->_renderTriangle();
	}

}