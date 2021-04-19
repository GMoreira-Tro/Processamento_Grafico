#pragma once
#include "Shaders.h"

const Ponto3d corDeFundo = Ponto3d(0.25f, 0.25f, 0.25f);

const float RAD2DEG = 180. / 3.14159265358979323846f;
const float DEG2RAD = 3.14159265358979323846f / 180.;

class GeometryHelper
{
public:
	void desenhaTriangulo(GLuint colorLoc, GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor);
	void desenhaTrianguloNapolitano(GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3);
	void desenhaTrianguloNapolitanoV2(GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3);
	void desenhaTrianguloComContorno(GLuint colorLoc, GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor, Ponto3d contorno);
	void desenhaTrianguloSemFundo(GLuint colorLoc, GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d contorno);
	void desenhaCirculo(GLuint colorLoc, GLuint shaderID,
		Ponto2d pontoInicial, Ponto3d cor, float fatorDeEscala);
	void contorno(GLuint colorLoc, Ponto3d cor, int deslocamento, int quantBytes);
};

