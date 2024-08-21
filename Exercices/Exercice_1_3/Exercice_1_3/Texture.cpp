#include "Texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* texturePath, const char* textureFormat, GLenum wrap_params, GLenum filter_params)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set texture wrapping params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_params);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_params);

	// Set texture filtering params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_params);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_params);

	// Load texture data
	// 1. Ensure image is vertically when loaded
	stbi_set_flip_vertically_on_load(true);

	// 2. load data
	LoadTextureData(texturePath, textureFormat);
}

void Texture::Activate(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::LoadTextureData(const char* filePath, const char* format)
{
	unsigned char* data = stbi_load(filePath, &mWidth, &mHeight, &mNrChannels, 0);
	if (data)
	{
		if (format != "png")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "ERROR::Failed loading texture" << std::endl;
	}
	stbi_image_free(data);
}
