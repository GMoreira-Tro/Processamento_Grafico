#pragma once
#include "GeometryHelper.h"


class MovementHelper
{
public:
	static float eixoHorizontal, eixoVertical;

	static void movimentacao_WASD(GLFWwindow* window, float velocidade);
	static void movimentacao_WASD(GLFWwindow* window, float velocidade, float limiteHorizontal, float limiteVertical);
	static void movimentacao_WASD_Espelhada(GLFWwindow* window, float velocidade, float limiteHorizontal, float limiteVertical);
};