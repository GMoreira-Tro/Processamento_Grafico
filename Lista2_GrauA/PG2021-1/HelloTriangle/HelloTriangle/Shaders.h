#pragma once

#include <iostream>
#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vetores.h"

using namespace std;

class Shaders
{
public:
	const GLchar* vertexShaderSource = "#version 450\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";

	const GLchar* fragmentShaderSource = "#version 450\n"
	"uniform vec4 inputColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = inputColor;\n"
	"}\n\0";

	const GLchar* vertexShaderSourceNapolitano = "#version 450\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 color;\n"
	"out vec4 inputColor;\n"
	"void main()\n"
	"{\n"
	"inputColor = vec4(color, 1.0);\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";

	const GLchar* fragmentShaderSourceNapolitano = "#version 450\n"
	"in vec4 inputColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = inputColor;\n"
	"}\n\0";

	static int setupShader();
	static int setupShaderNapolitano();
	static int setupGeometry(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3);
	static int setupGeometryNapolitano(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3,
		Ponto3d corVertice1, Ponto3d corVertice2, Ponto3d corVertice3);
	static int setupGeometryNapolitanoV2(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3,
		Ponto3d corVertice1, Ponto3d corVertice2, Ponto3d corVertice3);
};