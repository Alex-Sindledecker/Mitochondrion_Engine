#pragma once

#include <glad/glad.h>
#include <vector>

namespace gl
{

	using VertexBuffer = GLuint;
	using ElementBuffer = GLuint;
	using VertexArray = GLuint;

	struct VertexAttribute
	{
		VertexBuffer vbo;
		GLuint length;
		GLenum dataType;
		GLsizei stride;
		const void* offset;
		GLuint divisor = 0;
	};

	VertexBuffer createStaticVertexBuffer(size_t bufferSize, const void* buffer);
	VertexBuffer createDynamicVertexBuffer(size_t bufferSize, const void* buffer);
	ElementBuffer createStaticElementBuffer(size_t bufferSize, const void* buffer);
	ElementBuffer createDynamicElementBuffer(size_t bufferSize, const void* buffer);
	VertexArray createVertexArray(ElementBuffer ebo, std::vector<VertexAttribute> attributes);
	void deleteVertexBuffer(VertexBuffer vbo);
	void deleteElementBuffer(ElementBuffer ebo);
	void deleteVertexArray(VertexArray vao);

}