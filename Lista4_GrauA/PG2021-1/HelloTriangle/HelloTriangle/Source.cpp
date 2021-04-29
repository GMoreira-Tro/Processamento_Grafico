#pragma once

#include <conio.h>
#include <math.h>
#include "MovementHelper.h"
#include <locale.h>

GLuint colorLoc, shaderID;
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

        cout << "Sora, digita o n�mero do exerc�cio que tu queres (o extra � o '3'):";
        char exercicio = _getch();

        // Inicializa��o da GLFW
        glfwInit();

        // Cria��o da janela GLFW
        window = glfwCreateWindow(1920, 1080, "Akeno-sama <3", NULL, NULL);
        glfwMakeContextCurrent(window);

        // GLAD: carrega todos os ponteiros d fun��es da OpenGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;

        }

        // Obtendo as informa��es de vers�o
        const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
        const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
        cout << "Renderer: " << renderer << endl;
        cout << "OpenGL version supported " << version << endl;

        glClearColor(corDeFundo.x, corDeFundo.y, corDeFundo.z, 1.0f);

        MovementHelper::eixoHorizontal = MovementHelper::eixoVertical = 0;
        //Loop da aplica��o da janela.
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
                cout << "\n\nEsse exerc�cio n�o tem :(";
                break;
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        cout << "\n\n";
        glfwTerminate();
    }
}

void reajustaRazaoAspecto()
{
    razaoAspecto = (float)largura / altura;
}

void exercicio1()
{
    GeometryHelper::projecaoOrtografica(razaoAspecto, -10, 10, -10, 10);

    glPushMatrix(); //Empilha a matriz de transforma��o atual
    MovementHelper::movimentacao_WASD(window, 0.03f, 15, 7.5f);
    GeometryHelper::desenhaTriangulo(Ponto2d(-2.5, -2.5), Ponto2d(2.5, -2.5), Ponto2d(0, 2.5),
        Ponto3d(0.3f, 0, 0.9f));
    glPopMatrix(); //Desempilha a matriz de transforma��o atual
}