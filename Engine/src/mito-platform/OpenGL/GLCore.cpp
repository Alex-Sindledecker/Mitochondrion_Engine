#include "mepch.h"
#include "GLCore.h"

#include "mito/Debug/Debug.h"

#include <GLFW/glfw3.h>

namespace mito::gl
{

	void init()
	{
		MITO_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == true);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.13f, 0.32f, 0.58f, 1.f);
	}

	void terminate()
	{
		
	}

	void MITO_API clear(GLenum clearFlags)
	{
		glClear(clearFlags);
	}

	void MITO_API enableWireframeMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void MITO_API disableWireframeMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
	}

	void MITO_API _drawElements(VertexArray vao, GLuint count)
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void MITO_API _drawElementsInstanced(VertexArray vao, GLuint vertexCount, GLuint instanceCount)
	{
		glBindVertexArray(vao);
		glDrawElementsInstanced(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
		glBindVertexArray(0);
	}

	const OpenGLVersion MITO_API getGLVersion()
	{
		return { 4, 1, "#version 410 core" };
	}

}