#include "mepch.h"
#include "ShaderProgram.h"

#include "Core/Utilities.h"
#include "Core/Loaders.h"
#include "Core/Debug/EngineDebugger.h"

namespace gl
{

	ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexContents, fragmentContents;
		readFile(vertexPath, &vertexContents);
		readFile(fragmentPath, &fragmentContents);
		const char* vertexSrc = vertexContents.c_str();
		const char* fragmentSrc = fragmentContents.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
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
		readFile(vertexPath, &vertexContents);
		readFile(fragmentPath, &fragmentContents);
		readFile(fragmentPath, &geometryContents);
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

	ShaderProgram::ShaderProgram(ShaderProgram&& oldShader)
	{
		programID = oldShader.programID;
		oldShader.programID = 0;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(programID);
	}

	void ShaderProgram::bind()
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

	void ShaderProgram::setUniformVector4(const char* position, float* vector) const
	{
		glUniform4fv(glGetUniformLocation(programID, position), 1, vector);
	}

	void ShaderProgram::setUniformVector3(const char* position, float* vector) const
	{
		glUniform3fv(glGetUniformLocation(programID, position), 1, vector);
	}

	void ShaderProgram::setUniformVector2(const char* position, float* vector) const
	{
		glUniform2fv(glGetUniformLocation(programID, position), 1, vector);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& oldShader) noexcept
	{
		programID = oldShader.programID;
		oldShader.programID = 0;
		return *this;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram& oldShader) noexcept
	{
		programID = oldShader.programID;
		oldShader.programID = 0;
		return *this;
	}

	void ShaderProgram::checkShaderCompileStatus(GLuint id, const char* path)
	{
		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			glGetShaderInfoLog(id, sizeof(infoLog), 0, infoLog);
			EngineDebugger::log(util::formatString("{} Failed to compile!\n{}", infoLog), EngineDebugger::LogType::ERR);
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
			EngineDebugger::log(util::formatString("Failed to link shader program!!\n{}", infoLog), EngineDebugger::LogType::ERR);
		}
	}

}