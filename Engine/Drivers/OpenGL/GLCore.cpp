#include "mepch.h"
#include "GLCore.h"

#include <assert.h>
#include <GLFW/glfw3.h>

namespace gl
{

	bool init()
	{
		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
			return false;

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.13f, 0.32f, 0.58f, 1.f);

		return true;
	}

	void terminate()
	{
		
	}

	void clear(GLenum clearFlags)
	{
		glClear(clearFlags);
	}

	void enableWireframeMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void disableWireframeMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
	}

	void _drawElements(VertexArray vao, GLuint count)
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void _drawElementsInstanced(VertexArray vao, GLuint vertexBufferSize, GLuint instanceCount)
	{
		glBindVertexArray(vao);
		glDrawElementsInstanced(GL_TRIANGLES, vertexBufferSize, GL_UNSIGNED_INT, nullptr, instanceCount);
		glBindVertexArray(0);
	}

	const OpenGLVersion getGLVersion()
	{
		return { 4, 1, "#version 410 core" };
	}

}