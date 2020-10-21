#pragma once

#include "RendererAPI.h"

namespace Engine
{
	using Vbo = GLuint;
	using ShaderProgramGL = GLuint;

	struct VertexAttribute
	{
		Vbo vbo;
		GLenum type;
		GLsizei lenth;
		GLsizeiptr stride;
		void* offset;

		GLuint divisor = 0;
	};

	struct Vao
	{
		GLuint id;
		GLuint vertexCount;
	};

	class OpenGLRenderer : public RendererAPI
	{
	public:
		virtual RenderPipelineInitStatus init(GLFWwindow* window) override;
		virtual void clearActiveFramebuffer(BitField flags) override;
		virtual void setClearColor(const float r, const float g, const float b) override;
		virtual void enableWireframe() override;
		virtual void disableWireframe() override;
		virtual void renderTriangles(const Vao& vao);
		virtual void renderTrianglesInstanced(const Vao& vao, GLuint instances);
		virtual ShaderProgramGL createShaderProgram(const char* vertexSourcePath, const char* fragmentSourcePath, const char* geometrySourcePath = nullptr);
		virtual ShaderProgramGL createShaderProgram(const std::string& vertexSourcePath, const std::string& fragmentSourcePath, const std::string& geometrySourcePath = "");
		virtual Vbo createVBO(GLenum type, GLsizeiptr size, void* data);
		virtual Vao createVAO(const Vbo& indexBuffer, std::vector<VertexAttribute>& attributes);

		virtual void _renderTriangle() override;

	private:

	};

}