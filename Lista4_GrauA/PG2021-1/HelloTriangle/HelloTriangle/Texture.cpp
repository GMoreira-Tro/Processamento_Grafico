#include "Texture.h"
#include <iostream>

void Texture::FourApocalipseKnights()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::Texture(std::string path, unsigned int rendererID)
{
	this->filePath = path;
	this->rendererID = rendererID;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load(path.c_str(), &largura, &altura, &bitsPorPixel, 4);

	if (imageData)
	{
		glBindTexture(GL_TEXTURE_2D, rendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		FourApocalipseKnights();

		stbi_image_free(imageData);
		std::cout << "Carregou a textura!";
	}
	else
	{
		std::cout << "Ferrou a textura!";
	}
}

Texture::~Texture()
{
}

void Texture::Bind(unsigned int slot = 0)
{
}

void Texture::UnBind()
{
}

int Texture::GetWidth()
{
	return largura;
}

int Texture::GetHeight()
{
	return altura;
}
