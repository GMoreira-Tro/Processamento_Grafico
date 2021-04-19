#pragma once

#include <conio.h>
#include <math.h>
#include "GeometryHelper.h"

GLuint colorLoc, shaderID;

void exercicio1();
void exercicio2();
void exercicio3();
void exercicio4();
void exercicio5();

/*
Inicializador do programa.
*/
int main(void)
{

    GLFWwindow* window;

    while (true)
    {
        //Era pra limpar o buffer do teclado.
        fflush(stdin);

        cout << "Sora, digita o n�mero do exerc�cio que tu queres:";
        char exercicio = _getch();

        // Inicializa��o da GLFW
        glfwInit();

        // Cria��o da janela GLFW
        GLFWwindow* window = glfwCreateWindow(1920, 1080, "Akeno-sama <3", nullptr, nullptr);
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

        // Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Compilando e buildando o programa de shader
        shaderID = Shaders::setupShader();

        // Enviando a cor desejada (vec4) para o fragment shader
        // Utilizamos a vari�veis do tipo uniform em GLSL para armazenar esse tipo de info
        // que n�o est� nos buffers
        GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
        assert(colorLoc > -1);
        glUseProgram(shaderID);

        //Loop da aplica��o da janela.
        while (!glfwWindowShouldClose(window))
        {

            // Limpa o buffer de cor
            glClearColor(corDeFundo.x, corDeFundo.y, corDeFundo.z, 1.0f); //cor de fundo
            glClear(GL_COLOR_BUFFER_BIT);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            switch (exercicio)
            {
            case '1':
                exercicio1();
                break;
            case '2':
                exercicio2();
                break;
            case '3':
                exercicio3();
                break;
            case '4':
                exercicio4();
                break;
            case '5':
                exercicio5();
                break;
            default:
                glfwSetWindowShouldClose(window, GL_TRUE);
                cout << "\n\nEsse exerc�cio n�o tem :(";
                break;
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        cout << "\n\n";
        glfwTerminate();
    }
}

void exercicio1()
{

}

void exercicio2()
{

}

void exercicio3()
{

}

void exercicio4()
{

}

void exercicio5()
{

}