#include "pch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace Engine
{

	PipelineInitStatus Renderer::initForGLPipeline(GLLoadProc winProcAddr)
	{
		PipelineInitStatus status;

		if (!gladLoadGLLoader((GLADloadproc)winProcAddr))
		{
			status.code = RENDER_PIPELINE_INIT_FAILURE;
			status.string = "Failed to load OpenGL! Check window procedure addr...";
		}
		
		Renderer2D::init();
		Renderer3D::init();

		return status;
	}

	PipelineInitStatus Renderer::initForVKPipeline()
	{
		PipelineInitStatus status;

		Renderer2D::init();
		Renderer3D::init();

		return status;
	}

}