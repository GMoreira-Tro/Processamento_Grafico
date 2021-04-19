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

	static int setupShader();
	static int setupShaderNapolitano();
	static int setupGeometry(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3);
	static int setupGeometryNapolitano(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3,
		Ponto3d corVertice1, Ponto3d corVertice2, Ponto3d corVertice3);
	static int setupGeometryNapolitanoV2(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3,
		Ponto3d corVertice1, Ponto3d corVertice2, Ponto3d corVertice3);
};