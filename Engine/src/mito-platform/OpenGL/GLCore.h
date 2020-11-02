#pragma once

#include "mito/Core/MitochondriaAPI.h"

namespace mito::gl
{

	struct OpenGLVersion
	{
		u32_t major;
		u32_t minor;
		const char* str;
	};

	void MITO_API init();
	void MITO_API terminate();
	const OpenGLVersion MITO_API getGLVersion();

}