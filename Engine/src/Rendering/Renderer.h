#pragma once

#include "Renderers/OpenGLRenderer.h"
#include "Renderers/VulkanRenderer.h"

#include <GLFW/glfw3.h>

namespace Engine
{

	constexpr BitField CL_COLOR_BUFFER_FLAG = 0x00004000;
	constexpr BitField CL_DEPTH_BUFFER_FLAG = 0x000000100;
	constexpr BitField CL_STENCIL_BUFFER_FLAG = 0x000000400;

	class Renderer
	{
	public:
		static RenderPipelineInitStatus init(GLFWwindow* windowPtr);
		static void terminate();

		static void clearActiveFramebuffer(BitField flags = CL_COLOR_BUFFER_FLAG);
		static void setNormalizedClearColorRGB(const float r, const float g, const float b);
		static void setClearColorRGB(const u8_t r, const u8_t g, const u8_t b);

		//For debuging purposes only
		static void _renderTriangle();

		Renderer(const Renderer&) = delete;
		void operator=(const Renderer&) = delete;

	private:
		Renderer() {}
		~Renderer() {}

		static GLFWwindow* windowPtr;
		static RendererAPI* renderAPI;
	};

}