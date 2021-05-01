#include "MovementHelper.h"

float MovementHelper::eixoHorizontal;
float MovementHelper::eixoVertical;

void MovementHelper::movimentacao_WASD(GLFWwindow* window, float velocidade)
{
    //Se usasse 'else if', só conseguiríamos nos mover em uma direção por vez.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        eixoVertical += velocidade;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        eixoHorizontal -= velocidade;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        eixoVertical -= velocidade;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        eixoHorizontal += velocidade;
    }
    glTranslatef(eixoHorizontal, eixoVertical, 0);
}
void MovementHelper::movimentacao_WASD(GLFWwindow* window, float velocidade, float limiteDireito, float limiteCima,
    float limiteEsquerdo, float limiteBaixo)
{    
    //Se usasse 'else if', só conseguiríamos nos mover em uma direção por vez.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        eixoVertical += velocidade;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        eixoHorizontal -= velocidade;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        eixoVertical -= velocidade;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        eixoHorizontal += velocidade;
    }

    if (eixoVertical > limiteCima)
    {
        eixoVertical = limiteCima;
    }
    else if (eixoVertical < limiteBaixo)
    {
        eixoVertical = limiteBaixo;
    }

    if (eixoHorizontal > limiteDireito)
    {
        eixoHorizontal = limiteDireito;
    }
    else if (eixoHorizontal < limiteEsquerdo)
    {
        eixoHorizontal = limiteEsquerdo;
    }

    glTranslatef(eixoHorizontal, eixoVertical, 0);
}
void MovementHelper::movimentacao_WASD_Espelhada(GLFWwindow* window, float velocidade, float limiteDireito, float limiteCima,
    float limiteEsquerdo, float limiteBaixo)
{
    //Se usasse 'else if', só conseguiríamos nos mover em uma direção por vez.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        eixoVertical += velocidade;
        if (eixoVertical > limiteCima)
        {
            eixoVertical = limiteBaixo;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        eixoHorizontal -= velocidade;
        if (eixoHorizontal < limiteEsquerdo)
        {
            eixoHorizontal = limiteDireito;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        eixoVertical -= velocidade;
        if (eixoVertical < limiteBaixo)
        {
            eixoVertical = limiteCima;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        eixoHorizontal += velocidade;
        if (eixoHorizontal > limiteDireito)
        {
            eixoHorizontal = limiteEsquerdo;
        }
    }
    glTranslatef(eixoHorizontal, eixoVertical, 0);
}