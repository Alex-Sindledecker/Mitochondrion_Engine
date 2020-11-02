#pragma once

#include "mito/Core/MitochondriaAPI.h"

#include <glad/glad.h>
#include <vector>

namespace mito::gl
{

	using VertexBuffer = GLuint;
	using ElementBuffer = GLuint;
	using VertexArray = GLuint;

	struct MITO_API VertexAttribute
	{
		VertexBuffer vbo;
		GLuint length;
		GLenum dataType;
		GLsizei stride;
		const void* offset;
	};

	VertexBuffer MITO_API createStaticVertexBuffer(size_t bufferSize, const void* buffer);
	VertexBuffer MITO_API createDynamicVertexBuffer(size_t bufferSize, const void* buffer);
	ElementBuffer MITO_API createStaticElementBuffer(size_t bufferSize, const void* buffer);
	ElementBuffer MITO_API createDynamicElementBuffer(size_t bufferSize, const void* buffer);
	VertexArray MITO_API createVertexArray(ElementBuffer ebo, std::vector<VertexAttribute> attributes);

}