#ifndef SHADER_H
#define SHADER_H

// GL includes
#include "GL/glew.h"

class Shader
{
	GLuint shaderID;
	GLenum shaderType;
	bool isLoaded = false;

public:
	//----------------------------------------------------------------+
	// Loads and compiles shader from file.							  |
	// param shaderPath - Peth to the shader.						  |
	// param shaderType - Shader type.								  |
	//----------------------------------------------------------------+
	void loadShaderFromFile(const GLchar* shaderPath, GLenum shaderType);

	//----------------------------------------------------------------+
	// Cleans memory and internal variables.                 	  	  |
	//----------------------------------------------------------------+
	void deleteShader();

	// Getters
	bool isShaderLoaded()  const { return isLoaded; };
	GLuint getShaderID()   const { return shaderID; };
	GLenum getShaderType() const { return shaderType; };
};

#endif // !SHADER_H