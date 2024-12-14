#ifndef SPHERE_H
#define SPHERE_H

// GL Includes
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// GLM Mathematics
#include "glm/glm.hpp"

// Other Includes
#include "BufferObjects.h"

// Std. Includes
#include <vector>


// Default values
const glm::vec3 ORIGIN = { 0, 0, 0 };
const float RADIUS = 1.0f;
const unsigned int SECTOR_COUNT = 256; // 3
const unsigned int STACK_COUNT = 256;  // 4
const float SELF_ROTATION_SPEED = 10.0f;
const float ORBITAL_SPEED = 1.0f;

class Sphere
{
	glm::vec3 origin;
	float radius;
	int sectorCount;
	int stackCount;
	GLfloat selfRotationSpeed;

	GLfloat orbitRadius;
	GLfloat orbitalSpeed;

	std::vector <GLfloat> vertices; // Vector of sphere vertices
	std::vector <GLuint>   indices; // Sphere index vector (every 3 elements make a triangle)

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	GLuint VAO;
	BufferObjects<GLfloat> VBO;
	BufferObjects<GLuint> IBO;

public:
	//----------------------------------------------------------------+
	// Constructor creates sphere									  |
	// param sphereOrigin - Sphere origin.							  |
	// param sphereRadius - Sphere radiius.						      |
	// param sphereSectors - Quantity of sphere sectors(longitude)[>3]|
	// param sphereStacks - Quantity of sphere sectors(latitude)  [>4]|
	//----------------------------------------------------------------+
	Sphere(float sphereRadius = RADIUS, glm::vec3 sphereOrigin = ORIGIN, int sphereSectors = SECTOR_COUNT, int sphereStacks = STACK_COUNT);

	//----------------------------------------------------------------+
	// Adds rotation around its own axis and rotations aroud point    |
	// with some speed.												  |
	// param radius -  orbital radius.								  |
	// param orbitalSpeed -  Orbital speed.							  |
	// param selfRotationSpeed - ratation speed.					  |
	//----------------------------------------------------------------+
	void addRotation(GLfloat radius = 0, GLfloat orbitalSpeed = ORBITAL_SPEED, GLfloat selfRotationSpeed = SELF_ROTATION_SPEED, glm::vec3 point = ORIGIN);

	//----------------------------------------------------------------+
	// Generates VAO, VBO, IBO.								          |
	//----------------------------------------------------------------+
	void generateBuffers();

	//----------------------------------------------------------------+
	// Draw sphere. Have to call in game loop.				          |
	//----------------------------------------------------------------+
	void draw();

	~Sphere();

	// Getters 
	glm::vec3 getOrigin() const { return origin; };
	float getRadius()     const { return radius; };
	int getSectorCount()  const { return sectorCount; };
	int getStackCount()   const { return stackCount; };
	GLuint getVAO()		  const { return VAO; };
	std::vector<GLfloat> getVertices() const { return vertices; };
	std::vector<GLuint> getIndices()   const { return indices; };
	glm::mat4 getModelMatrix()         const { return modelMatrix; };

	// Setters
	void setModelMatrix(glm::mat4 model) { modelMatrix = model; };
private:
	//----------------------------------------------------------------+
	// Fills two vectors: vertices & indices.						  |
	//----------------------------------------------------------------+
	void makeVertices();
};

#endif // !SPHERE_H