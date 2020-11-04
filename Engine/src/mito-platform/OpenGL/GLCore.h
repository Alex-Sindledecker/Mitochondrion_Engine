#pragma once

#include "mito/Core/MitochondriaAPI.h"

#include "mito-platform/OpenGL/VertexArray.h"
#include "mito-platform/OpenGL/ShaderProgram.h"
#include "mito-platform/OpenGL/Texture.h"

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
	void MITO_API clear(GLenum clearFlags = GL_COLOR_BUFFER_BIT);
	void MITO_API enableWireframeMode();
	void MITO_API disableWireframeMode();
	void MITO_API _drawElements(VertexArray vao, GLuint count);
	void MITO_API _drawElementsInstanced(VertexArray vao, GLuint vertexCount, GLuint instanceCount);
	const OpenGLVersion MITO_API getGLVersion();

}