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
void MovementHelper::movimentacao_WASD(GLFWwindow* window, float velocidade, float limiteHorizontal, float limiteVertical)
{
    //Se usasse 'else if', só conseguiríamos nos mover em uma direção por vez.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (eixoVertical < limiteVertical)
        {
            eixoVertical += velocidade;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (eixoHorizontal > -limiteHorizontal)
        {
            eixoHorizontal -= velocidade;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (eixoVertical > -limiteVertical)
        {
            eixoVertical -= velocidade;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (eixoHorizontal < limiteHorizontal)
        {
            eixoHorizontal += velocidade;
        }
    }

    glTranslatef(eixoHorizontal, eixoVertical, 0);
}
void MovementHelper::movimentacao_WASD_Espelhada(GLFWwindow* window, float velocidade, float limiteHorizontal, float limiteVertical)
{
    //Se usasse 'else if', só conseguiríamos nos mover em uma direção por vez.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        eixoVertical += velocidade;
        if (eixoVertical > limiteVertical)
        {
            eixoVertical *= -1;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        eixoHorizontal -= velocidade;
        if (eixoHorizontal < -limiteHorizontal)
        {
            eixoHorizontal *= -1;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        eixoVertical -= velocidade;
        if (eixoVertical < -limiteVertical)
        {
            eixoVertical *= -1;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        eixoHorizontal += velocidade;
        if (eixoHorizontal > limiteHorizontal)
        {
            eixoHorizontal *= -1;
        }
    }
    glTranslatef(eixoHorizontal, eixoVertical, 0);
}