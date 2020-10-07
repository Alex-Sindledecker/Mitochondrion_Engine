#pragma once

#include "RendererAPI.h"

namespace Engine
{

	class VulkanRenderer : public RendererAPI
	{
	public:
		virtual RenderPipelineInitStatus init(GLFWwindow* window) override;
		virtual void clearActiveFramebuffer(BitField flags) override;
		virtual void _renderTriangle() override;
		virtual void setClearColor(const float r, const float g, const float b) override;
	};

}