#ifndef TEXTURE_H
#define TEXTURE_H

// GL includes
#include "GL/glew.h"

// Std. Includes
#include <string>
#include <map>
#include <memory>


class Texture
{
	GLuint textureID = 0;
	GLboolean isLoaded = false;
	std::string imgPath;
public:
	Texture(std::string path) : imgPath(path) {};
	~Texture();

	//----------------------------------------------------------------+
	// Setts texture wrapping parameter.					     	  |
	// param S - Param for S axis.									  |
	// param T - Param for T axis.									  |
	//----------------------------------------------------------------+
	void setTextureWrappingParam(GLenum S = GL_REPEAT, GLenum T = GL_REPEAT);

	//----------------------------------------------------------------+
	// Setts texture filtering parameter.					     	  |
	// param Min - Texture filtering for minifying (downwards).       |
	// param Mag - Texture filtering for magnifying (scaling up).     |
	//----------------------------------------------------------------+
	void setTextureFilteringParam(GLenum Min = GL_LINEAR_MIPMAP_LINEAR, GLenum Mag = GL_LINEAR);

	//----------------------------------------------------------------+
	// Loads image from @imgPath (initialization in the constructor). |
	//----------------------------------------------------------------+
	void loadTexture();

	//----------------------------------------------------------------+
	// Fast load for a typical case.                                  |
	//----------------------------------------------------------------+
	void fastLoad();

	//----------------------------------------------------------------+
	// Bind and activate texture.                                     |
	//----------------------------------------------------------------+
	void useTexture();

	//----------------------------------------------------------------+
	// Cleans memory and internal variables.                 	  	  |
	//----------------------------------------------------------------+
	void clearTexture();

	// Getters
	GLuint getTextureID()       const { return textureID; };
	GLboolean isTextureLoaded() const { return isLoaded; };
	std::string getImgPath()    const { return imgPath; };

private:
};

#endif // !TEXTURE_H
