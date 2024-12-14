#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

// Other includes
#include "Shader.h"

class ShaderProgram
{
	GLuint shaderProgramID;
	bool isLinked = false;
public:
	//----------------------------------------------------------------+
	// Creates new shader program.								      |
	//----------------------------------------------------------------+
	void createProgram();

	//----------------------------------------------------------------+
	// Adds shader to current shader program.					      |
	// param shader - Shader to be added to the program				  |
	// return True, if the shader has been added or false otherwise.  |
	//----------------------------------------------------------------+
	bool addShaderToProgram(const Shader& shader);

	//-------------------------------------------------------------------------------+
	// Links the program. If the function succeeds, shader program is ready to use.  |
	// return True, if the shader has been linked or false otherwise.				 |
	//-------------------------------------------------------------------------------+
	bool linkProgram();

	//----------------------------------------------------------------+
	// Uses this shader program(makes current).					      |
	//----------------------------------------------------------------+
	void useProgram() const;

	//----------------------------------------------------------------+
	// Deletes this shader program.								      |
	//----------------------------------------------------------------+
	void deleteProgram();

	// Getters
	GLuint getShaderProgramID() const;
};

#endif // !SHADER_PROGRAMM_H
