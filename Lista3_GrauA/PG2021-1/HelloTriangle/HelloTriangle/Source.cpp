#pragma once

#include <conio.h>
#include <math.h>
#include "GeometryHelper.h"
#include <locale.h>

GLuint colorLoc, shaderID;
GLFWwindow* window;
int altura, largura;
float razaoAspecto, eixoHorizontal = 0, eixoVertical = 0;

void exercicio1();
void exercicio2();
void exercicio3();

void reajustaRazaoAspecto();

/*
Inicializador do programa.
*/
int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    while (true)
    {
        //Era pra limpar o buffer do teclado.
        fflush(stdin);

        cout << "Sora, digita o número do exercício que tu queres (o extra é o '3'):";
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

        // Obtendo as informações de versão
        const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
        const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
        cout << "Renderer: " << renderer << endl;
        cout << "OpenGL version supported " << version << endl;

        glClearColor(corDeFundo.x, corDeFundo.y, corDeFundo.z, 1.0f);

        eixoHorizontal = eixoVertical = 0;
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

void movimentacao_WASD(float velocidade)
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
void movimentacao_WASD(float velocidade, float limiteHorizontal, float limiteVertical)
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
void movimentacao_WASD_Espelhada(float velocidade, float limiteHorizontal, float limiteVertical)
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

void exercicio1()
{
    projecaoOrtografica(-10, 10, -10, 10);

    glPushMatrix(); //Empilha a matriz de transformação atual
    glTranslatef(0, -7.5f, 0);
    GeometryHelper::desenhaTriangulo(Ponto2d(-2.5 , -2.5), Ponto2d(2.5, -2.5), Ponto2d(0, 2.5),
        Ponto3d(0.9f, 0, 0.3f));
    glPopMatrix(); //Desempilha a matriz de transformação atual

    GeometryHelper::desenhaTriangulo(Ponto2d(-2.5, -2.5), Ponto2d(2.5, -2.5), Ponto2d(0, 2.5),
        Ponto3d(0.3f, 0, 0.9f));

    glPushMatrix(); //Empilha a matriz de transformação atual
    glTranslatef(0, 7.5f, 0);
    GeometryHelper::desenhaTriangulo(Ponto2d(-2.5, -2.5), Ponto2d(2.5, -2.5), Ponto2d(0, 2.5),
        Ponto3d(0.9f, 0.9f, 0.3f));
    glPopMatrix(); //Desempilha a matriz de transformação atual
}

void exercicio2()
{
    projecaoOrtografica(-10, 10, -10, 10);

    glPushMatrix();
    movimentacao_WASD(0.03f, 15, 7.5f);
    GeometryHelper::desenhaTriangulo(Ponto2d(-2.5f, -2.5f),
        Ponto2d(2.5f, -2.5f),
        Ponto2d(0, 2.5f),
        Ponto3d(0.9f, 0, 0.3f));
    glPopMatrix();

    //Só pra ver se os push matrix e pop matrix tão certos.
    projecaoOrtografica(-10, 10, -10, 10);
    GeometryHelper::desenhaQuadrilatero(Ponto2d(1, 1), Ponto2d(2, 1), Ponto2d(2, 2), Ponto2d(1, 2),
        Ponto3d(0.9f, 0.9f, 0.3f));
}

void exercicio3()
{
    projecaoOrtografica(-10, 10, -10, 10);

    glPushMatrix();
    movimentacao_WASD_Espelhada(0.03f, 8.5f, 5);
    GeometryHelper::desenhaCirculo(
        Ponto2d(eixoHorizontal, eixoVertical),
        Ponto3d(0.9f, 0, 0.3f),
        1);
    glPopMatrix();
}