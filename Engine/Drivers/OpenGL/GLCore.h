#pragma once

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace gl
{

	struct OpenGLVersion
	{
		int major;
		int minor;
		const char* str;
	};

	bool init();
	void terminate();
	void clear(GLenum clearFlags = GL_COLOR_BUFFER_BIT);
	void enableWireframeMode();
	void disableWireframeMode();
	void _drawElements(VertexArray vao, GLuint count);
	void _drawElementsInstanced(VertexArray vao, GLuint vertexCount, GLuint instanceCount);
	const OpenGLVersion getGLVersion();

}