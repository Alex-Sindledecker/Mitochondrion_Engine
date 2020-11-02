#pragma once

#include "mito/Core/MitochondriaAPI.h"
#include <glm/glm.hpp>

namespace mito::gl
{

	class MITO_API ShaderProgram
	{
	public:
		ShaderProgram(const char* vertexPath, const char* fragmentPath);
		ShaderProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
		~ShaderProgram();

		void bindProgram();
		void setUniformMatrix4(const char* position, const glm::mat4& value) const;
		void setUniformMatrix3(const char* position, const glm::mat3& value) const;
		void setUniformVector4(const char* position, const glm::vec4& value) const;
		void setUniformVector3(const char* position, const glm::vec3& value) const;
		void setUniformVector2(const char* position, const glm::vec2& value) const;
		void setUniformFloat(const char* position, float value) const;
		void setUniformInt(const char* position, int value) const;

	private:
		GLuint programID;

	private:
		void checkShaderCompileStatus(GLuint id, const char* path);
		void checkProgramLinkStatus();
	};

}