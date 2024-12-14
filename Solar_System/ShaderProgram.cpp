// GL includes
#include "GL/glew.h"

// Other includes
#include "ShaderProgram.h"

// Std. Includes
#include <iostream>

void ShaderProgram::createProgram()
{
	shaderProgramID = glCreateProgram();
}

bool ShaderProgram::addShaderToProgram(const Shader& shader)
{
	if (!shader.isShaderLoaded())
		return false;

	glAttachShader(shaderProgramID, shader.getShaderID());
	return true;
}

bool ShaderProgram::linkProgram()
{
	glLinkProgram(shaderProgramID);
	int linkStatus;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkStatus);
	isLinked = linkStatus == GL_TRUE;

	// Print linking errors if any
	GLint success;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);

		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	return isLinked;
}

void ShaderProgram::deleteProgram()
{
	if (!isLinked) {
		return;
	}

	glDeleteProgram(shaderProgramID);
	isLinked = false;
}

void ShaderProgram::useProgram() const
{
	if (isLinked) {
		glUseProgram(shaderProgramID);
	}
}

GLuint ShaderProgram::getShaderProgramID() const
{
	return shaderProgramID;
}
