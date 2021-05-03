#pragma once

#include <stdlib.h>
#include <time.h>
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

Texture* enemiesTextures[5];
Texture* numeros[10];
Texture* background;
Texture* backgroundGameOver;
Texture* playAgain;
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
void desenhaPontuacao();
void GerenciadorInimigos();
void validaPassagemInimigo();
void validaColisao();

#pragma endregion

class Enemy
{
public:
    float deslocamentoHorizontal;
    int texturaId;

    Enemy(int texturaId)
    {
        this->deslocamentoHorizontal = 0;
        this->texturaId = texturaId;
    }
};
Enemy* vetorInimigos[3];
unsigned short quantInimigos = 0;

/*
Inicializador do programa.
*/
int main(int argc, char* argv[])
{
    //Musiquinha
    PlaySound("Sons/danganronpa.wav", NULL, SND_ASYNC | SND_LOOP);

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
    thread threadGerenciaInimigos(GerenciadorInimigos);

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
    threadGerenciaInimigos.join();
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

    //Desenha o personagem emo
    glPushMatrix(); //Empilha a matriz de transformação atual
    MovementHelper::movimentacao_Pulo(window, (float)gameLevel/100 * (float)largura / 1000, 5);
    GeometryHelper::desenhaQuadrilateroTexturizado(characterSpriteSheet[spriteSheetIndex]->rendererID,
        Ponto2d(-12, -8),
        Ponto2d(-9, -8),
        Ponto2d(-9, -5),
        Ponto2d(-12, -5),
        Ponto3d(1, 1, 1));
    glPopMatrix(); //Desempilha a matriz de transformação atual

    desenhaPontuacao();

    for (int i = 0; i < quantInimigos; i++)
    {
        glPushMatrix(); //Empilha a matriz de transformação atual
        GeometryHelper::desenhaQuadrilateroTexturizado(vetorInimigos[i]->texturaId,
            Ponto2d(12 - vetorInimigos[i]->deslocamentoHorizontal, -8),
            Ponto2d(11 - vetorInimigos[i]->deslocamentoHorizontal, -8),
            Ponto2d(11 - vetorInimigos[i]->deslocamentoHorizontal, -5),
            Ponto2d(12 - vetorInimigos[i]->deslocamentoHorizontal, -5),
            Ponto3d(1, 1, 1));
        glPopMatrix(); //Desempilha a matriz de transformação atual

        vetorInimigos[i]->deslocamentoHorizontal += (float)gameLevel / 100 * (float)largura/1000;
    }

    if (quantInimigos > 0)
    {
        validaColisao();
        validaPassagemInimigo();
    }
}

/*
Validar uma colisao com o inimigo.
*/
void validaColisao()
{
    if (vetorInimigos[0]->deslocamentoHorizontal > 22 && 
        vetorInimigos[0]->deslocamentoHorizontal < 24)
    {
        if (MovementHelper::eixoVertical < 2)
        {
            gameOver();
        }
    }
}

/*
Validar um inimigo que foi embora.
*/
void validaPassagemInimigo()
{
    if (vetorInimigos[0]->deslocamentoHorizontal > 25)
    {
        if (gamePoints < 999)
        {
            gamePoints++;
        }
        quantInimigos--;
        if (quantInimigos > 0)
        {
            vetorInimigos[0] = vetorInimigos[1];
            if (quantInimigos > 1)
            {
                vetorInimigos[1] = vetorInimigos[2];
            }
        }
    }
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
        enemiesTextures[i] = new Texture("Texturas/Enemies/enemy" + to_string(i) + ".png", rendererID);
    }

    //Carrega o background
    GLuint rendererID;
    glGenTextures(1, &rendererID);
    background = new Texture("Texturas/background.jpg", rendererID);

    glGenTextures(1, &rendererID);
    backgroundGameOver = new Texture("Texturas/backgroundGameOver.jpg", rendererID);

    glGenTextures(1, &rendererID);
    playAgain = new Texture("Texturas/PlayAgain.png", rendererID);

    //Carrega a Sprite Sheet do nosso herói emo
    for (int i = 0; i < 10; i++)
    {
        GLuint rendererID;
        glGenTextures(1, &rendererID);
        characterSpriteSheet[i] = new Texture("Texturas/EmoSpriteSheet/tile00" + to_string(i) +
            ".png", rendererID);
    }

    //Carrega a textura dos números
    for (int i = 0; i < 10; i++)
    {
        GLuint rendererID;
        glGenTextures(1, &rendererID);
        numeros[i] = new Texture("Texturas/Numeros/" + to_string(i) +
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
    while (true)
    {
        Sleep(MilissengundosAtualizacaoGameLevel);
        if (fimDeJogo || gameLevel == 999)
        {
            continue;
        }
        gameLevel++;
    }
}

/*
Função da thread que gerencia inimigos.
*/
void GerenciadorInimigos()
{
    while (true)
    {
        if (fimDeJogo || quantInimigos == 3)
        {
            continue;
        }

        srand(time(NULL));

        vetorInimigos[quantInimigos] = new Enemy(enemiesTextures[rand() % 5]->rendererID);
        quantInimigos++;
        Sleep(200 + 2000 / gameLevel);
    }
}

/*
Função pra chamar logo ao dar Game Over.
*/
void gameOver()
{
    PlaySound("Sons/gameOver.wav", NULL, SND_ASYNC);
    fimDeJogo = true;
}

/*
Update da tela de Game Over.
*/
void gameOverUpdate()
{
    GeometryHelper::projecaoOrtografica(razaoAspecto, -10, 10, -10, 10);

    GeometryHelper::desenhaQuadrilateroTexturizado(backgroundGameOver->rendererID,
        Ponto2d(-10 * razaoAspecto, -10),
        Ponto2d(10 * razaoAspecto, -10),
        Ponto2d(10 * razaoAspecto, 10),
        Ponto2d(-10 * razaoAspecto, 10),
        Ponto3d(1, 1, 1));

    GeometryHelper::desenhaQuadrilateroTexturizado(playAgain->rendererID,
        Ponto2d(-2 * razaoAspecto, -5),
        Ponto2d(2 * razaoAspecto, -5),
        Ponto2d(2 * razaoAspecto, -4),
        Ponto2d(-2 * razaoAspecto, -4),
        Ponto3d(1, 1, 1));

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        fimDeJogo = false;
        PlaySound("Sons/danganronpa.wav", NULL, SND_ASYNC | SND_LOOP);
        gameLevel = 1;
        gamePoints = 0;
        quantInimigos = 0;
    }
}

/*
Função para desenhar a pontuação.
*/
void desenhaPontuacao()
{
    int pontuacaoCaracteres = gamePoints;

    GeometryHelper::desenhaQuadrilateroTexturizado(numeros[pontuacaoCaracteres%10]->rendererID,
        Ponto2d(-12, 4),
        Ponto2d(-9, 4),
        Ponto2d(-9, 6),
        Ponto2d(-12, 6),
        Ponto3d(1, 1, 1));

    pontuacaoCaracteres /= 10;

    GeometryHelper::desenhaQuadrilateroTexturizado(numeros[pontuacaoCaracteres % 10]->rendererID,
        Ponto2d(-13.5, 4),
        Ponto2d(-10.5, 4),
        Ponto2d(-10.5, 6),
        Ponto2d(-13.5, 6),
        Ponto3d(1, 1, 1));

    pontuacaoCaracteres /= 10;

    GeometryHelper::desenhaQuadrilateroTexturizado(numeros[pontuacaoCaracteres % 10]->rendererID,
        Ponto2d(-15, 4),
        Ponto2d(-12, 4),
        Ponto2d(-12, 6),
        Ponto2d(-15, 6),
        Ponto3d(1, 1, 1));
}