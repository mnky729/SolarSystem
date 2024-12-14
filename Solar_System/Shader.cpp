#include "Shader.h"

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void Shader::loadShaderFromFile(const GLchar* shaderPath, GLenum shaderType)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string Code;
	std::ifstream shaderFile;

	//Check that ifstream can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// Read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// Convert stream into string
		Code = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* shaderCode = Code.c_str();

	// 2. Compile shaders
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);
	// Print compile errors if any
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::" << shaderType
			<< "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderType = shaderType;
	isLoaded = true;
}

void Shader::deleteShader()
{
	if (!isLoaded)
		return;

	isLoaded = false;
	glDeleteShader(shaderID);
}
