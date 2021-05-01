#pragma once

#include <conio.h>
#include <math.h>
#include <locale.h>
#include "MovementHelper.h"
#include "Texture.h"

GLuint colorLoc, shaderID, texturesID[5];
GLFWwindow* window;
int altura, largura;
float razaoAspecto;

void exercicio1();

void reajustaRazaoAspecto();

/*
Inicializador do programa.
*/
int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    while (true)
    {
        //Limpando o buffer do teclado na marra.
        while (_kbhit())
        {
            _getch();
        }

        cout << "Sora, digita o número do exercício que tu queres:";
        char exercicio = _getch();

        // Inicialização da GLFW
        glfwInit();

        // Criação da janela GLFW
        window = glfwCreateWindow(1920, 1080, "Akeno-sama <3", NULL, NULL);
        glfwMakeContextCurrent(window);

        // GLAD: carrega todos os ponteiros d funções da OpenGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;
        }

        glClearColor(corDeFundo.x, corDeFundo.y, corDeFundo.z, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glGenTextures(3, texturesID);
        Texture* dxd = new Texture("Texturas/snk.png", texturesID[0]);
        //carregaTextura(texturesID[1], "images/painted_brick.png");
        //carregaTextura(texturesID[2], "images/wood.png");

        MovementHelper::eixoHorizontal = MovementHelper::eixoVertical = 0;
        //Loop da aplicação da janela.
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glfwGetFramebufferSize(window, &largura, &altura);
            glViewport(0, 0, largura, altura);

            reajustaRazaoAspecto();

            switch (exercicio)
            {
            case '1':
                exercicio1();
                break;
            default:
                glfwSetWindowShouldClose(window, GL_TRUE);
                cout << "\n\nEsse exercício não tem :(";
                break;
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        cout << "\n\n";
        glDisable(GL_TEXTURE_2D);
        glDeleteTextures(sizeof(texturesID) / sizeof(GLuint), texturesID);
        glfwTerminate();
    }
}

void reajustaRazaoAspecto()
{
    razaoAspecto = (float)largura / altura;
}

void exercicio1()
{
    //GeometryHelper::projecaoOrtografica(razaoAspecto, -10, 10, -10, 10);

    glPushMatrix(); //Empilha a matriz de transformação atual
    MovementHelper::movimentacao_WASD(window, 0.00005f * largura, 10 * razaoAspecto -2.5f, 7.5f, 
        -10 * razaoAspecto + 2.5f, -7.5f);
    //GeometryHelper::desenhaTrianguloTexturizado(texturesID[0],
    //    Ponto2d(-2.5, -2.5), Ponto2d(2.5, -2.5), Ponto2d(0, 2.5),
    //    Ponto3d(0.3f, 0, 0.9f));
    GeometryHelper::desenhaQuadrilateroTexturizado(texturesID[0], Ponto2d(-1, -1),
        Ponto2d(1, -1), Ponto2d(1, 1), Ponto2d(-1, 1), Ponto3d(1, 1, 1));
    glPopMatrix(); //Desempilha a matriz de transformação atual
}