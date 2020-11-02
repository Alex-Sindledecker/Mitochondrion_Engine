#include "mepch.h"
#include "ShaderProgram.h"

#include "mito/Debug/Debug.h"
#include "mito/Core/FileManager.h"

namespace mito::gl
{

	ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexContents, fragmentContents;
		loadFile(vertexPath, &vertexContents);
		loadFile(fragmentPath, &fragmentContents);
		const char* vertexSrc = vertexContents.c_str();
		const char* fragmentSrc = fragmentContents.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, 0);
		glShaderSource(fragmentShader, 1, &fragmentSrc, 0);
		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		checkShaderCompileStatus(vertexShader, vertexPath);
		checkShaderCompileStatus(fragmentShader, fragmentPath);

		programID = glCreateProgram();
		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);
		glLinkProgram(programID);

		checkProgramLinkStatus();

		glDetachShader(programID, vertexShader);
		glDetachShader(programID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		std::string vertexContents, fragmentContents, geometryContents;
		loadFile(vertexPath, &vertexContents);
		loadFile(fragmentPath, &fragmentContents);
		loadFile(fragmentPath, &geometryContents);
		const char* vertexSrc = vertexContents.c_str();
		const char* fragmentSrc = fragmentContents.c_str();
		const char* geometrySrc = geometryContents.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, 0);
		glShaderSource(fragmentShader, 1, &fragmentSrc, 0);
		glShaderSource(geometryShader, 1, &geometryPath, 0);
		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);
		glCompileShader(geometryShader);

		checkShaderCompileStatus(vertexShader, vertexPath);
		checkShaderCompileStatus(fragmentShader, fragmentPath);
		checkShaderCompileStatus(geometryShader, geometryPath);

		programID = glCreateProgram();
		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);
		glAttachShader(programID, geometryShader);
		glLinkProgram(programID);

		checkProgramLinkStatus();

		glDetachShader(programID, vertexShader);
		glDetachShader(programID, fragmentShader);
		glDetachShader(programID, geometryShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(geometryShader);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(programID);
	}

	void ShaderProgram::bindProgram()
	{
		glUseProgram(programID);
	}

	void ShaderProgram::setUniformMatrix4(const char* position, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(programID, position), 1, GL_FALSE, &value[0][0]);
	}

	void ShaderProgram::setUniformMatrix3(const char* position, const glm::mat3& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(programID, position), 1, GL_FALSE, &value[0][0]);
	}

	void ShaderProgram::setUniformVector4(const char* position, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(programID, position), 1, &value[0]);
	}

	void ShaderProgram::setUniformVector3(const char* position, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(programID, position), 1, &value[0]);
	}

	void ShaderProgram::setUniformVector2(const char* position, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(programID, position), 1, &value[0]);
	}

	void ShaderProgram::setUniformFloat(const char* position, float value) const
	{
		glUniform1f(glGetUniformLocation(programID, position), value);
	}

	void ShaderProgram::setUniformInt(const char* position, int value) const
	{
		glUniform1i(glGetUniformLocation(programID, position), value);
	}

	void ShaderProgram::checkShaderCompileStatus(GLuint id, const char* path)
	{
		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			glGetShaderInfoLog(id, sizeof(infoLog), 0, infoLog);
			Debug::log(Debug::ERR_LOG, "{} Failed to compile!\n{}", path, infoLog);
		}
	}

	void ShaderProgram::checkProgramLinkStatus()
	{
		int success;
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			glGetProgramInfoLog(programID, sizeof(infoLog), 0, infoLog);
			Debug::log(Debug::ERR_LOG, "Failed to link shader program!!\n{}", infoLog);
		}
	}

}