#pragma once

#include "RenderCore.h"
#include "Renderers/Renderer2D.h"
#include "Renderers/Renderer3D.h"

#define RENDER_PIPELINE_INIT_SUCCESS 0
#define RENDER_PIPELINE_INIT_FAILURE -1

namespace Engine
{

	struct ENGINE_API PipelineInitStatus
	{
		int code = RENDER_PIPELINE_INIT_SUCCESS;
		const char* string = "Success!";
	};

	class ENGINE_API Renderer
	{
	public:
		typedef void(*GLProcFunc)();
		typedef void(*VKProcFunc)();
		typedef GLProcFunc(*GLLoadProc)(const char* name);
		typedef VKProcFunc(*VKLoadProc)(const char* name);
	public:
		static PipelineInitStatus initForGLPipeline(GLLoadProc winProcAddr);
		static PipelineInitStatus initForVKPipeline();

		Renderer(const Renderer&) = delete;
		void operator=(const Renderer&) = delete;

	private:
		Renderer() {}
		~Renderer() {}
	};

}