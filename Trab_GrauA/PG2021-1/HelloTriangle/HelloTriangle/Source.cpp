#pragma once

#include <conio.h>
#include <math.h>
#include "MovementHelper.h"
#include "Texture.h"
#include <thread>
#include <windows.h>

#define milissegundosAtualizacaoSpriteSheet 100

GLuint colorLoc, shaderID;

Texture* enemies[5];
Texture* background;
Texture* characterSpriteSheet[10];
unsigned int spriteSheetIndex = 0;

GLFWwindow* window;

int altura, largura;
float razaoAspecto;

void carregaTexturas();
void gameUpdate();
void reajustaRazaoAspecto();
void atualizaSpriteSheetIndex();

/*
Inicializador do programa.
*/
int main(void)
{
    // Inicialização da GLFW
    glfwInit();

    // Criação da janela GLFW
    window = glfwCreateWindow(1920, 1080, "Emo runner", NULL, NULL);
    glfwMakeContextCurrent(window);

    // GLAD: carrega todos os ponteiros d funções da OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
    }

    carregaTexturas();
    thread threadAtualizaSpriteSheet(atualizaSpriteSheetIndex);

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

        gameUpdate();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    cout << "\n\n";
    glDisable(GL_TEXTURE_2D);
    glfwTerminate();
    threadAtualizaSpriteSheet.join();
}

/*
Update principal do game.
*/
void gameUpdate()
{
    GeometryHelper::projecaoOrtografica(razaoAspecto, -10, 10, -10, 10);

    GeometryHelper::desenhaQuadrilateroTexturizado(background->rendererID, 
        Ponto2d(-10 * razaoAspecto, -10),
        Ponto2d(10 * razaoAspecto, -10), 
        Ponto2d(10 * razaoAspecto, 10), 
        Ponto2d(-10 * razaoAspecto, 10), 
        Ponto3d(1, 1, 1));

    glPushMatrix(); //Empilha a matriz de transformação atual
    MovementHelper::movimentacao_Pulo(window, 0.00005f * altura, 5);
    GeometryHelper::desenhaQuadrilateroTexturizado(characterSpriteSheet[spriteSheetIndex]->rendererID,
        Ponto2d(-12, -8),
        Ponto2d(-9, -8),
        Ponto2d(-9, -5),
        Ponto2d(-12, -5),
        Ponto3d(1,1,1));
    glPopMatrix(); //Desempilha a matriz de transformação atual
}

/*
Reajustar a razão do aspecto da tela (largura/altura).
*/
void reajustaRazaoAspecto()
{
    razaoAspecto = (float)largura / altura;
}

/*
Método para carregar todas as texturas usadas no game.
*/
void carregaTexturas()
{
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //Carrega inimigos
    for (int i = 0; i < 5; i++)
    {
        GLuint rendererID;
        glGenTextures(1, &rendererID);
        enemies[i] = new Texture("Texturas/Enemies/enemy" + to_string(i) + ".png", rendererID);
    }

    //Carrega o background
    GLuint rendererID;
    glGenTextures(1, &rendererID);
    background = new Texture("Texturas/background.jpg", rendererID);

    //Carrega a Sprite Sheet do nosso herói emo
    for (int i = 0; i < 10; i++)
    {
        GLuint rendererID;
        glGenTextures(1, &rendererID);
        characterSpriteSheet[i] = new Texture("Texturas/EmoSpriteSheet/tile00" + to_string(i) +
            ".png", rendererID);
    }
}

/*
Função da thread que atualiza a Sprite Sheet.
*/
void atualizaSpriteSheetIndex()
{
    while(true)
    {
        Sleep(milissegundosAtualizacaoSpriteSheet);
        spriteSheetIndex = (spriteSheetIndex + 1) % 10;
    }
}