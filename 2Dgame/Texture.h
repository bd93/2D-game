#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies/stb_image.h"

class Texture
{
private:
	GLuint texture;
	int width, height, nrChannels;
public:
	Texture(std::string imagePath)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD_TEXTURE/n";
		}

		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}
	Texture()
	{
	}
	void bind() const
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	void unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

#endif