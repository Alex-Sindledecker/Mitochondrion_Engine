#include "pch.h"
#include "VulkanRenderer.h"

namespace Engine
{
	RenderPipelineInitStatus VulkanRenderer::init(GLFWwindow* window)
	{
		RendererAPI::init(window);

		RenderPipelineInitStatus status;

		status.code = RENDER_PIPELINE_INIT_FAILURE;
		status.string = "Vulkan is not yet supported!";

		return status;
	}

	void VulkanRenderer::clearActiveFramebuffer(BitField flags)
	{
	}

	void VulkanRenderer::_renderTriangle()
	{
	}

	void VulkanRenderer::setClearColor(const float r, const float g, const float b)
	{
	}

}