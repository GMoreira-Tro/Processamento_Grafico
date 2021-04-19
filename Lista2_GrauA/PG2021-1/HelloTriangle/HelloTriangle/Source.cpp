#pragma once

#include <conio.h>
#include <math.h>
#include "GeometryHelper.h"

GLuint colorLoc, shaderID;
int altura, largura;
float razaoAspecto;

void exercicio1();
void exercicio2();
void exercicio3();
void exercicio4();
void exercicio5();

void reajustaRazaoAspecto();
void projecaoOrtografica(GLdouble esquerda, GLdouble direita, GLdouble baixo, GLdouble alto, GLdouble zPerto, GLdouble zLonge);

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

        cout << "Sora, digita o número do exercício que tu queres:";
        char exercicio = _getch();

        // Inicialização da GLFW
        glfwInit();

        // Criação da janela GLFW
        GLFWwindow* window = glfwCreateWindow(1920, 1080, "Akeno-sama <3", NULL, NULL);
        glfwMakeContextCurrent(window);

        // GLAD: carrega todos os ponteiros d funções da OpenGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;

        }

        // Obtendo as informações de versão
        const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
        const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
        cout << "Renderer: " << renderer << endl;
        cout << "OpenGL version supported " << version << endl;

        glClearColor(corDeFundo.x, corDeFundo.y, corDeFundo.z, 1.0f);

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
                cout << "\n\nEsse exercício não tem :(";
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

void projecaoOrtografica(GLdouble esquerda, GLdouble direita, GLdouble baixo, GLdouble alto, GLdouble zPerto = 1, GLdouble zLonge = -1)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(esquerda * razaoAspecto, direita * razaoAspecto, baixo, alto, zPerto, zLonge);
}

void projecaoOrtograficaDesproporcional(GLdouble esquerda, GLdouble direita, GLdouble baixo, GLdouble alto, GLdouble zPerto = 1, GLdouble zLonge = -1)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(esquerda, direita, baixo, alto, zPerto, zLonge);
}

void exercicio1()
{
    projecaoOrtografica(-10, 10, -10, 10);
    GeometryHelper::desenhaTriangulo(colorLoc, shaderID, Ponto2d(-3, -3), Ponto2d(3, -3), Ponto2d(0, 0),
        Ponto3d(0.9f, 0, 0.3f));

}

void exercicio2()
{
    projecaoOrtograficaDesproporcional(-200, 200, -200, 200);
    
    glColor3f(0.75f, 0.25f, 0.05f);
    glBegin(GL_QUADS);
    {
        glVertex2f(-50, -50);
        glVertex2f(50, -50);
        glVertex2f(50, 50);
        glVertex2f(-50, 50);
    }
    glEnd();
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