#pragma once

#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <string>

class Texture
{
private:
	unsigned int rendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int largura;
	int altura;
	int bitsPorPixel;

	void FourApocalipseKnights();

public:
	Texture(std::string path, unsigned int rendererID);
	~Texture();
	void Bind(unsigned int slot);
	void UnBind();
	int GetWidth();
	int GetHeight();
};

