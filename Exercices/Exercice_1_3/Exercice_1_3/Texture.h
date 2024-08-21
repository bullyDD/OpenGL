#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLAD/glad.h"
#include <iostream>

class Texture
{
public:
	unsigned int textureID;

	Texture(const char* texturePath, const char* textureFormat="jpg", GLenum wrap_params = GL_REPEAT, GLenum filter_params = GL_LINEAR);
	void Activate(GLenum textureUnit);

private:
	//====== MEMBER VARIABLES =========//

	int mWidth, mHeight, mNrChannels;
	void LoadTextureData(const char* filePath, const char* format);
};

#endif
