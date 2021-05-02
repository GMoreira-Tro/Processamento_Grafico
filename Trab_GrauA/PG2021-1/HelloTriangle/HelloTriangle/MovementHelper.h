#pragma once
#include "GeometryHelper.h"


class MovementHelper
{
public:
	static float eixoHorizontal, eixoVertical;

	static void movimentacao_WASD(GLFWwindow* window, float velocidade);
	static void movimentacao_WASD(GLFWwindow* window, float velocidade, float limiteDireito, float limiteCima,
		float limiteEsquerdo, float limiteBaixo);
	static void movimentacao_WASD_Espelhada(GLFWwindow* window, float velocidade, float limiteDireito, float limiteCima,
		float limiteEsquerdo, float limiteBaixo);
	static void movimentacao_Pulo(GLFWwindow* window, float velocidade, float alturaPulo);

private:
	static void subindoPulo(float velocidade, float alturaPulo);
	static void descendoPulo(float velocidade);
};