#ifndef BUFFER_OBJECTS_H
#define BUFFER_OBJECTS_H

// GL Includes
#include <GL/glew.h>

// Std. Includes
#include <vector>
#include <iostream>

template <typename T>
class BufferObjects
{
	GLuint bufferID = 0;
	int bufferType;
	uint32_t uploadedDataSize;
	std::vector<T> rawData;

	bool isDataUploaded = false;
	bool isBufferCreated = false;
public:
	//----------------------------------------------------------------+
	// Creates a new BO, with optional reserved buffer size.      	  |
	// param reserveElements - Quantity of reserved elements.		  |
	//----------------------------------------------------------------+
	void createBO(uint32_t reserveElements = 0);

	//----------------------------------------------------------------+
	// Binds BO (makes current)									  	  |
	// param bufferType - Type of the bound buffer					  |
	//----------------------------------------------------------------+
	void bindBO(GLenum bufferType = GL_ARRAY_BUFFER);

	//----------------------------------------------------------------+
	// Adds data to the in - memory buffer, before they get uploaded. |
	// param Data - Vector of data					 				  |
	//----------------------------------------------------------------+
	void addData(std::vector<T> Data);

	//--------------------------------------------------------------------------+
	// Uploads gathered data to the GPU memory.Now the VBO is ready to be used. |
	// param usageHint - Hint for OpenGL, how is the data intended to be used.  |
	//--------------------------------------------------------------------------+
	void uploadDataToGPU(GLenum usageHint = GL_STATIC_DRAW);

	//----------------------------------------------------------------+
	// Deletes BO and cleans memory and internal variables.  	  	  |
	//----------------------------------------------------------------+
	void deleteBO();

	// Getters
	GLuint getBufferID() { return bufferID; };
	uint32_t getBufferSize();
};


template <typename T>
void BufferObjects<T>::createBO(uint32_t reserveElements)
{
	if (isBufferCreated)
	{
		std::cerr << "ERROR::This buffer is already created! You need to delete it before re-creating it!" << std::endl;
		return;
	}

	glGenBuffers(1, &bufferID);
	if (reserveElements > 0)
	{
		this->rawData.reserve(reserveElements);
	}

	isBufferCreated = true;
}

template <typename T>
void BufferObjects<T>::bindBO(GLenum bufferType)
{
	if (!isBufferCreated)
	{
		std::cerr << "ERROR::This buffer is not created yet! You cannot bind it before you create it!" << std::endl;
		return;
	}

	this->bufferType = bufferType;
	glBindBuffer(this->bufferType, bufferID);
}

template <typename T>
void BufferObjects<T>::addData(std::vector<T> Data)
{
	rawData.insert(rawData.end(), Data.begin(), Data.end());
}

template <typename T>
void BufferObjects<T>::uploadDataToGPU(GLenum usageHint)
{
	if (!isBufferCreated)
	{
		std::cerr << "ERROR::This buffer is not created yet! Call createVBO before uploading data to GPU!" << std::endl;
		return;
	}

	glBufferData(bufferType,
		rawData.size() * sizeof(T),
		&rawData[0],
		usageHint);

	isDataUploaded = true;
	uploadedDataSize = static_cast<uint32_t>(rawData.size() * sizeof(T));
	rawData.clear();
}

template <typename T>
uint32_t BufferObjects<T>::getBufferSize()
{
	return isDataUploaded ? uploadedDataSize : 0;
}

template <typename T>
void BufferObjects<T>::deleteBO()
{
	if (isBufferCreated)
	{
		glDeleteBuffers(1, &bufferID);
		isDataUploaded = false;
		isBufferCreated = false;
	}

	rawData.clear();
}

#endif // !BufferObjects