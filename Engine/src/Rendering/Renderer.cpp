#include "pch.h"

#include "Renderer.h"

#include <glad/glad.h>

namespace Engine
{

	PipelineInitStatus Renderer::init(LoadProc winProcFunc)
	{
		#ifdef ENGINE_USE_VULKAN
			return initVK();
		#else
			return initGL(winProcFunc);
		#endif
	}

	void Renderer::terminate()
	{
	}

	void Renderer::clearActiveFramebuffer(BitField flags)
	{
		glClear(flags);
	}

	void Renderer::setNormalizedClearColorRGB(const float r, const float g, const float b)
	{
		glClearColor(r, g, b, 1.f);
	}

	void Renderer::setClearColorRGB(const u8 r, const u8 g, const u8 b)
	{
		glClearColor(float(r / 255.f), float(g / 255.f), float(b / 255.f), 1.f);
	}

	PipelineInitStatus Renderer::initVK()
	{
		PipelineInitStatus status;

		status.code = RENDER_PIPELINE_INIT_FAILURE;
		status.string = "Vulkan is not yet supported!";
	
		return status;
	}

	PipelineInitStatus Renderer::initGL(LoadProc winProcFunc)
	{
		PipelineInitStatus status;

		if (!gladLoadGLLoader((GLADloadproc)winProcFunc))
		{
			status.code = RENDER_PIPELINE_INIT_FAILURE;
			status.string = "Failed to load OpenGL! Check window procedure addr...";
		}

		Renderer2D::init();
		Renderer3D::init();

		return status;
	}

}