#pragma once
#include "Shaders.h"

const Ponto3d corDeFundo = Ponto3d(0.9f, 0.15f, 0.3f);

const double RAD2DEG = 180. / 3.14159265358979323846f;
const double DEG2RAD = 3.14159265358979323846f / 180.;

class GeometryHelper
{
public:
	static void desenhaTriangulo(
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor);
	static void desenhaTrianguloTexturizado(GLuint textureID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor);
	static void desenhaTrianguloComContorno(
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor, Ponto3d contorno);
	static void desenhaTrianguloSemFundo(
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d contorno);
	static void desenhaTriangulo(GLuint colorLoc, GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor);
	static void desenhaTrianguloNapolitano(GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3);
	static void desenhaTrianguloNapolitanoV2(GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3);
	static void desenhaTrianguloComContorno(GLuint colorLoc, GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor, Ponto3d contorno);
	static void desenhaTrianguloSemFundo(GLuint colorLoc, GLuint shaderID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d contorno);
	static void desenhaQuadrilatero(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto2d vertice4,
		Ponto3d cor);
	static void desenhaQuadrilateroTexturizado(GLuint textureID,
		Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto2d vertice4,
		Ponto3d cor);
	static void desenhaQuadrilateroComContorno(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto2d vertice4,
		Ponto3d cor, Ponto3d contorno);
	static void desenhaQuadrilateroSemFundo(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto2d vertice4,
		Ponto3d contorno);
	static void desenhaCirculo(GLuint colorLoc, GLuint shaderID,
		Ponto2d pontoInicial, Ponto3d cor, float fatorDeEscala);
	static void desenhaCirculo(
		Ponto2d pontoInicial, Ponto3d cor, float fatorDeEscala);
	static void contorno(GLuint colorLoc, Ponto3d cor, int deslocamento, int quantBytes);
	static void contorno(Ponto3d cor, int deslocamento, int quantBytes);
	static void projecaoOrtografica(GLdouble razaoAspecto, GLdouble esquerda, GLdouble direita, GLdouble baixo, GLdouble alto,
		GLdouble zPerto = 1, GLdouble zLonge = -1);
	static void projecaoOrtograficaDesproporcional(GLdouble esquerda, GLdouble direita, GLdouble baixo, GLdouble alto, 
		GLdouble zPerto = 1, GLdouble zLonge = -1);
};

