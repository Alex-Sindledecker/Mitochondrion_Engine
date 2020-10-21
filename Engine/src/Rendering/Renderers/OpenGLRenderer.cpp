#include "pch.h"
#include "Core/FileManager.h"
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

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_CULL_FACE);

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

	void OpenGLRenderer::enableWireframe()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void OpenGLRenderer::disableWireframe()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OpenGLRenderer::renderTriangles(const Vao& vao)
	{
		glBindVertexArray(vao.id);
		glDrawElements(GL_TRIANGLES, vao.vertexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void OpenGLRenderer::renderTrianglesInstanced(const Vao& vao, GLuint instances)
	{
		glBindVertexArray(vao.id);
		glDrawElementsInstanced(GL_TRIANGLES, vao.vertexCount, GL_UNSIGNED_INT, 0, instances);
		glBindVertexArray(0);
	}

	ShaderProgramGL OpenGLRenderer::createShaderProgram(const char* vertexSourcePath, const char* fragmentSourcePath, const char* geometrySourcePath)
	{
		std::string vertexShaderStr;
		std::string fragmentShaderStr;
		loadFile(vertexSourcePath, &vertexShaderStr);
		loadFile(fragmentSourcePath, &fragmentShaderStr);

		const char* vertexSource = vertexShaderStr.c_str();
		const char* fragmentSource = fragmentShaderStr.c_str();

		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertexShaderID, 1, &vertexSource, 0);
		glShaderSource(fragmentShaderID, 1, &fragmentSource, 0);
		glCompileShader(vertexShaderID);
		glCompileShader(fragmentShaderID);

		ShaderProgramGL program = glCreateProgram();
		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragmentShaderID);
		if (geometrySourcePath != nullptr)
		{
			std::string geometryShaderStr;
			loadFile(fragmentSourcePath, &fragmentShaderStr);
			
			const char* geometrySource = geometryShaderStr.c_str();

			GLuint geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShaderID, 1, &geometrySource, 0);
			glCompileShader(geometryShaderID);

			glAttachShader(program, geometryShaderID);

			glLinkProgram(program);
			glDetachShader(program, geometryShaderID);
			glDeleteShader(geometryShaderID);
		}
		else
			glLinkProgram(program);

		glDetachShader(program, vertexShaderID);
		glDeleteShader(vertexShaderID);
		glDetachShader(program, fragmentShaderID);
		glDeleteShader(fragmentShaderID);

		return program;
	}

	ShaderProgramGL OpenGLRenderer::createShaderProgram(const std::string& vertexSourcePath, const std::string& fragmentSourcePath, const std::string& geometrySourcePath)
	{
		return createShaderProgram(vertexSourcePath.c_str(), fragmentSourcePath.c_str(), geometrySourcePath.c_str());
	}

	Vbo OpenGLRenderer::createVBO(GLenum type, GLsizeiptr size, void* data)
	{
		Vbo vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(type, vbo);
		glBufferData(type, size, data, GL_STATIC_DRAW);
		glBindBuffer(type, 0);
		return vbo;
	}

	Vao OpenGLRenderer::createVAO(const Vbo& indexBuffer, std::vector<VertexAttribute>& attributes)
	{
		Vao vao;

		glGenVertexArrays(1, &vao.id);
		glBindVertexArray(vao.id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		for (int i = 0; i < attributes.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, attributes[i].vbo);
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attributes[i].lenth, attributes[i].type, GL_FALSE, attributes[i].stride, attributes[i].offset);
			glVertexAttribDivisor(i, attributes[i].divisor);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		return vao;
	}

	void OpenGLRenderer::_renderTriangle()
	{
		static Vao vao;
		static GLuint programID = 0;
		static float uTheta = 0.f; //Uniform theta
		uTheta += 0.0005;

		if (vao.id == 0)
		{
			float vertices[] =
			{
				 0.000f,		1.f, 0.f, 0.f,
				 2.356f,		0.f, 1.f, 0.f,
				 3.926f,		0.f, 0.f, 1.f
			};

			float offsets[] = 
			{
				-0.5f, -0.5f,
				-0.5f,  0.5f,
				 0.5f, -0.5f,
				 0.5f,  0.5f,
			};

			GLuint indices[] = { 0, 1, 2 };

			Vbo elementBufferObject = createVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);
			Vbo vertexBufferObject = createVBO(GL_ARRAY_BUFFER, sizeof(vertices), vertices);
			Vbo offsetsVBO = createVBO(GL_ARRAY_BUFFER, sizeof(offsets), offsets);

			VertexAttribute vertexAttribute;
			vertexAttribute.vbo = vertexBufferObject;
			vertexAttribute.type = GL_FLOAT;
			vertexAttribute.lenth = 1;
			vertexAttribute.stride = 4 * sizeof(float);
			vertexAttribute.offset = (void*)0;

			VertexAttribute colorAttribute = vertexAttribute;
			vertexAttribute.lenth = 3;
			vertexAttribute.offset = (void*)(1 * sizeof(float));

			VertexAttribute offsetAttribute;
			offsetAttribute.vbo = offsetsVBO;
			offsetAttribute.type = GL_FLOAT;
			offsetAttribute.lenth = 2;
			offsetAttribute.stride = 2 * sizeof(float);
			offsetAttribute.offset = (void*)0;
			offsetAttribute.divisor = 1;

			std::vector<VertexAttribute> attributes = { colorAttribute, vertexAttribute, offsetAttribute };

			vao = createVAO(elementBufferObject, attributes);
			vao.vertexCount = 3;

			programID = createShaderProgram("src/Rendering/Renderers/Shaders/ExampleVertex.glsl",
											"src/Rendering/Renderers/Shaders/ExampleFragment.glsl");
		}

		glUseProgram(programID);
		glUniform1f(glGetUniformLocation(programID, "theta"), uTheta);
		renderTrianglesInstanced(vao, 4);
	}

}