#pragma once

#include <math.h>
#include "MovementHelper.h"
#include "Texture.h"
#include <thread>
#include <windows.h>
#include <GL/glut.h>

#define MilissegundosAtualizacaoSpriteSheet 100
#define MilissengundosAtualizacaoGameLevel 10000

GLuint colorLoc, shaderID;

#pragma region Texturas

Texture* enemies[5];
Texture* background;
Texture* characterSpriteSheet[10];
unsigned int spriteSheetIndex = 0;

#pragma endregion


GLFWwindow* window;

int altura, largura;
float razaoAspecto;

#pragma region GameInfo

//Fator de velocidade da cena.
unsigned int gameLevel = 1;
//Pontuação.
unsigned short gamePoints = 0;
//Deu fim de jogo?
bool fimDeJogo = false;

#pragma endregion

#pragma region Methods

void carregaTexturas();
void gameUpdate();
void gameOverUpdate();
void reajustaRazaoAspecto();
void atualizaSpriteSheetIndex();
void atualizaGameLevel();
void gameOver();
void desenhaTexto(const char* texto, int x, int y);

#pragma endregion

/*
Inicializador do programa.
*/
int main(int argc, char* argv[])
{
    //Musiquinha
     //PlaySound("Sons/danganronpa.wav", NULL, SND_ASYNC | SND_LOOP);

    // Inicialização da GLFW
    glfwInit();

    //Inicialização da GLUT
    glutInit(&argc, argv);

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
    thread threadAtualizaGameLevel(atualizaGameLevel);

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

        if (fimDeJogo)
        {
            gameOverUpdate();
        }
        else
        {
            gameUpdate();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    cout << "\n\n";
    glDisable(GL_TEXTURE_2D);
    glfwTerminate();
    threadAtualizaSpriteSheet.join();
    threadAtualizaGameLevel.join();
}

/*
Update principal do game.
*/
void gameUpdate()
{
    //GeometryHelper::projecaoOrtografica(razaoAspecto, -10, 10, -10, 10);

    //GeometryHelper::desenhaQuadrilateroTexturizado(background->rendererID, 
    //    Ponto2d(-10 * razaoAspecto, -10),
    //    Ponto2d(10 * razaoAspecto, -10), 
    //    Ponto2d(10 * razaoAspecto, 10), 
    //    Ponto2d(-10 * razaoAspecto, 10), 
    //    Ponto3d(1, 1, 1));

    ////Desenha o personagem emo
    //glPushMatrix(); //Empilha a matriz de transformação atual
    //MovementHelper::movimentacao_Pulo(window, 0.00005f * altura, 5);
    //GeometryHelper::desenhaQuadrilateroTexturizado(characterSpriteSheet[spriteSheetIndex]->rendererID,
    //    Ponto2d(-12, -8),
    //    Ponto2d(-9, -8),
    //    Ponto2d(-9, -5),
    //    Ponto2d(-12, -5),
    //    Ponto3d(1,1,1));
    //glPopMatrix(); //Desempilha a matriz de transformação atual

    string pontosString = "124124";
    glColor3f(0, 1, 0);
    desenhaTexto(pontosString.data(), -150, 150);
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
        Sleep(MilissegundosAtualizacaoSpriteSheet);
        spriteSheetIndex = (spriteSheetIndex + 1) % 10;
    }
}

/*
Função da thread que atualiza o Game Level.
*/
void atualizaGameLevel()
{
    while (gameLevel < 999)
    {
        Sleep(MilissengundosAtualizacaoGameLevel);
        gameLevel++;
    }
}

/*
Função pra chamar logo ao dar Game Over.
*/
void gameOver()
{
    PlaySound("Sons/gameOver.wav", NULL, SND_ASYNC);
}

/*
Update da tela de Game Over.
*/
void gameOverUpdate()
{

}

/*
Função para desenhar um texto na tela do contexto OpenGL.
@param texto Texto a ser impresso.
@param x Posição horizontal do texto.
@param y Posição vertical do texto.
*/
void desenhaTexto(const char* texto, int x, int y)
{
    glPushMatrix();
    // Posição no universo onde o texto será colocado          
    glRasterPos2f(x, y);
    // Exibe caractere a caractere
    while (*texto)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *texto++);
    }
    glPopMatrix();
}