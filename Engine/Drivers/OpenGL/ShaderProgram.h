#pragma once

#include <glm/glm.hpp>

namespace gl
{

	class ShaderProgram
	{
	public:
		ShaderProgram(const char* vertexPath, const char* fragmentPath);
		ShaderProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
		ShaderProgram(ShaderProgram&& oldShader);
		ShaderProgram() {}
		~ShaderProgram();

		void bind();
		void setUniformMatrix4(const char* position, const glm::mat4& value) const;
		void setUniformMatrix3(const char* position, const glm::mat3& value) const;
		void setUniformVector4(const char* position, const glm::vec4& value) const;
		void setUniformVector3(const char* position, const glm::vec3& value) const;
		void setUniformVector2(const char* position, const glm::vec2& value) const;
		void setUniformFloat(const char* position, float value) const;
		void setUniformInt(const char* position, int value) const;

		ShaderProgram& operator=(ShaderProgram&& oldShader) noexcept;
		ShaderProgram& operator=(ShaderProgram& oldShader) noexcept;

	private:
		GLuint programID;

	private:
		void checkShaderCompileStatus(GLuint id, const char* path);
		void checkProgramLinkStatus();
	};

}