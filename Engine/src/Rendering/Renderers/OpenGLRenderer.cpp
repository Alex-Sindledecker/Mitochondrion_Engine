#include "pch.h"

#include <glad/glad.h>
#include "OpenGLRenderer.h"

namespace Engine
{
	RenderPipelineInitStatus OpenGLRenderer::init(GLFWwindow* window)
	{
		RendererAPI::init(window);

		RenderPipelineInitStatus status;

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			status.code = RENDER_PIPELINE_INIT_FAILURE;
			status.string = "Failed to load OpenGL! Check window procedure addr...";
		}

		return status;
	}

	void OpenGLRenderer::clearActiveFramebuffer(BitField flags)
	{
		glClear(flags);
	}

	void OpenGLRenderer::setClearColor(const float r, const float g, const float b)
	{
		glClearColor(r, g, b, 1.f);
	}

	void OpenGLRenderer::_renderTriangle()
	{
		static GLuint vao = 0;
		static GLuint programID = 0;
		static float uTheta = 0.f; //Uniform theta
		uTheta += 0.0005;

		if (vao == 0)
		{
			float vertices[] =
			{
				 0.000f,		1.f, 0.f, 0.f,
				 2.356f,		0.f, 1.f, 0.f,
				 3.926f,		0.f, 0.f, 1.f
			};

			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(1 * sizeof(float)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			const char* v = "#version 410 core\n\
			layout (location = 0) in float offset;\
			layout (location = 1) in vec3 color;\
			uniform float theta = 0.f;\
			out vec3 fragColor;\
			void main()\
			{\
				vec2 pos;\
				pos.x = 0.5 * sin(theta - offset);\
				pos.y = 0.5 * cos(theta - offset);\
				gl_Position = vec4(pos, 0.f, 1.f);\
				fragColor = color;\
			}";

			const char* f = "#version 410 core\n\
			in vec3 fragColor;\
			out vec3 color;\
			void main()\
			{\
				color = fragColor;\
			}";

			GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(vShader, 1, &v, nullptr);
			glShaderSource(fShader, 1, &f, nullptr);
			glCompileShader(vShader);
			glCompileShader(fShader);

			programID = glCreateProgram();
			glAttachShader(programID, vShader);
			glAttachShader(programID, fShader);
			glLinkProgram(programID);
		}

		glUseProgram(programID);
		glUniform1f(glGetUniformLocation(programID, "theta"), uTheta);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

}