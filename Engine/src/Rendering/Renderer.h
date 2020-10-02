#pragma once

#include "Core.h"
#include "Renderers/Renderer2D.h"
#include "Renderers/Renderer3D.h"

#define RENDER_PIPELINE_INIT_SUCCESS 0
#define RENDER_PIPELINE_INIT_FAILURE -1

namespace Engine
{

	using BitField = u32;

	struct PipelineInitStatus
	{
		int code = RENDER_PIPELINE_INIT_SUCCESS;
		const char* string = "Success!";
	};

	constexpr BitField CL_COLOR_BUFFER_FLAG = 0x00004000;
	constexpr BitField CL_DEPTH_BUFFER_FLAG = 0x000000100;
	constexpr BitField CL_STENCIL_BUFFER_FLAG = 0x000000400;

	class Renderer
	{
	public:
		typedef void(*ProcFunc)();
		typedef ProcFunc(*LoadProc)(const char* name);
	public:
		static PipelineInitStatus init(LoadProc winProcFunc);
		static void terminate();

		static void clearActiveFramebuffer(BitField flags = CL_COLOR_BUFFER_FLAG);
		static void setNormalizedClearColorRGB(const float r, const float g, const float b);
		static void setClearColorRGB(const u8 r, const u8 g, const u8 b);

		Renderer(const Renderer&) = delete;
		void operator=(const Renderer&) = delete;

	private:
		static PipelineInitStatus initVK();
		static PipelineInitStatus initGL(LoadProc winProcFunc);

		Renderer() {}
		~Renderer() {}
	};

}