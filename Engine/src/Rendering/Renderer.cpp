#include "pch.h"

#include "Renderer.h"

#include <glad/glad.h>

namespace Engine
{

	PipelineInitStatus Renderer::init(LoadProc winProcFunc)
	{
		#ifdef ENGINE_USE_VULKAN
			return initVK();
		#else
			return initGL(winProcFunc);
		#endif
	}

	void Renderer::terminate()
	{
	}

	void Renderer::clearActiveFramebuffer(BitField flags)
	{
		glClear(flags);
	}

	void Renderer::setNormalizedClearColorRGB(const float r, const float g, const float b)
	{
		glClearColor(r, g, b, 1.f);
	}

	void Renderer::setClearColorRGB(const u8_t r, const u8_t g, const u8_t b)
	{
		glClearColor(float(r / 255.f), float(g / 255.f), float(b / 255.f), 1.f);
	}

	void Renderer::_renderTriangle()
	{
		static GLuint vao = 0;
		static GLuint programID = 0;

		if (vao == 0)
		{
			float vertices[] = 
			{
				 0.0f,  0.5f,		1.f, 0.f, 0.f,
				-0.5f, -0.5f,		0.f, 1.f, 0.f,
				 0.5f, -0.5f,		0.f, 0.f, 1.f
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
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			const char* v = "#version 410 core\n\
			layout (location = 0) in vec2 pos;\
			layout (location = 1) in vec3 color;\
			out vec3 fragColor;\
			void main()\
			{\
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
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	PipelineInitStatus Renderer::initVK()
	{
		PipelineInitStatus status;

		status.code = RENDER_PIPELINE_INIT_FAILURE;
		status.string = "Vulkan is not yet supported!";
	
		return status;
	}

	PipelineInitStatus Renderer::initGL(LoadProc winProcFunc)
	{
		PipelineInitStatus status;

		if (!gladLoadGLLoader((GLADloadproc)winProcFunc))
		{
			status.code = RENDER_PIPELINE_INIT_FAILURE;
			status.string = "Failed to load OpenGL! Check window procedure addr...";
		}

		Renderer2D::init();
		Renderer3D::init();

		return status;
	}

}