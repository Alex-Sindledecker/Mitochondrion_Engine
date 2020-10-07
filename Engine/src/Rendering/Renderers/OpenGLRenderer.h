#pragma once

#include "RendererAPI.h"

namespace Engine
{

	class OpenGLRenderer : public RendererAPI
	{
	public:
		virtual RenderPipelineInitStatus init(GLFWwindow* window) override;
		virtual void clearActiveFramebuffer(BitField flags) override;
		virtual void setClearColor(const float r, const float g, const float b) override;
		virtual void _renderTriangle() override;
	};

}