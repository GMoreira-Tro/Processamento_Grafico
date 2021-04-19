#include "GeometryHelper.h"

/*
Imprime um triângulo de acordo com os vértices.
@param colorLoc Alocador de cor.
@param shaderID Identificador do programa de shader.
@param vertice1 Primeiro vértice.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
@param cor Cor do triângulo.
*/
void GeometryHelper::desenhaTriangulo(GLuint colorLoc, GLuint shaderID,
    Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor)
{
    //Jeito mais 'simples', mas menos interesssante
    //glBegin(GL_TRIANGLES);
    //glVertex2f(vertice1.x, vertice1.y);
    //glVertex2f(vertice2.x, vertice2.y);
    //glVertex2f(vertice3.x, vertice3.y);
    //glUniform4f(colorLoc, 0.6f, 0.0f, 0.6f, 0);
    //glEnd();

    GLuint VAO = Shaders::setupGeometry(vertice1, vertice2, vertice3);
    glUniform4f(colorLoc, cor.x, cor.y, cor.z, 1.0f);
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*
Imprime um triângulo de acordo com os vértices.
@param shaderID Identificador do programa de shader.
@param vertice1 Primeiro vértice.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
*/
void GeometryHelper::desenhaTrianguloNapolitano(GLuint shaderID,
    Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3)
{
    GLuint VAO = Shaders::setupGeometryNapolitano(vertice1, vertice2, vertice3, Ponto3d(1, 0, 0),
        Ponto3d(0, 1, 0), Ponto3d(0, 0, 1));
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*
Imprime um triângulo de acordo com os vértices.
@param shaderID Identificador do programa de shader.
@param vertice1 Primeiro vértice.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
*/
void GeometryHelper::desenhaTrianguloNapolitanoV2(GLuint shaderID,
    Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3)
{
    GLuint VAO = Shaders::setupGeometryNapolitanoV2(vertice1, vertice2, vertice3, Ponto3d(1, 0, 0),
        Ponto3d(0, 1, 0), Ponto3d(0, 0, 1));
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*
Imprime um triângulo de acordo com os vértices.
@param colorLoc Alocador de cor.
@param shaderID Identificador do programa de shader.
@param vertice1 Primeiro vértice.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
@param cor Cor do triângulo.
@param contorno Contorno do triângulo
*/
void GeometryHelper::desenhaTrianguloComContorno(GLuint colorLoc, GLuint shaderID,
    Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor, Ponto3d contorno)
{
    //Desenho do triângulo
    //GL_TRIANGLES - preenchimento do triângulo
    GLuint VAO = Shaders::setupGeometry(vertice1, vertice2, vertice3);
    glUniform4f(colorLoc, cor.x, cor.y, cor.z, 1.0f);
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Chamada de desenho - drawcall
    // CONTORNO - GL_LINE_LOOP
    glUniform4f(colorLoc, contorno.x, contorno.y, contorno.z, 1.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glBindVertexArray(0);
}

/*
Imprime um triângulo de acordo com os vértices.
@param shaderID Identificador do programa de shader.
@param colorLoc Alocador de cor.
@param shaderID Identificador do programa de shader.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
@param contorno Contorno do triângulo
*/
void GeometryHelper::desenhaTrianguloSemFundo(GLuint colorLoc, GLuint shaderID,
    Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d contorno)
{
    //Desenho do triângulo
    //GL_TRIANGLES - preenchimento do triângulo
    GLuint VAO = Shaders::setupGeometry(vertice1, vertice2, vertice3);
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 3);

    // Chamada de desenho - drawcall
    // CONTORNO - GL_LINE_LOOP
    glUniform4f(colorLoc, contorno.x, contorno.y, contorno.z, 1.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glBindVertexArray(0);
}

/*
Imprime um círculo de acordo com um ponto inicial.
@param colorLoc Alocador de cor.
@param shaderID Identificador do programa de shader.
@param pontoInicial Ponto central do círculo.
@param cor Cor do círculo.
@param fatorDeEscala Fator de escala para multiplicar o círculo.
*/
void GeometryHelper::desenhaCirculo(GLuint colorLoc, GLuint shaderID,
    Ponto2d pontoInicial, Ponto3d cor, float fatorDeEscala)
{
    for (int i = 0; i < 360; i++)
    {
        float angle = i * DEG2RAD;
        float postAngle = (i + 1) * DEG2RAD;

        desenhaTriangulo(colorLoc, shaderID,
            Ponto2d(pontoInicial.x, pontoInicial.y),
            Ponto2d(sin(angle) * fatorDeEscala + pontoInicial.x, cos(angle) * fatorDeEscala + pontoInicial.y),
            Ponto2d(sin(postAngle) * fatorDeEscala + pontoInicial.x, cos(postAngle) * fatorDeEscala + pontoInicial.y),
            Ponto3d(cor.x, cor.y, cor.z));

        glUniform4f(colorLoc, 1, 1, 1, 1);
        glDrawArrays(GL_LINE_LOOP, 1, 2);
        glBindVertexArray(0);
    }
}

void GeometryHelper::contorno(GLuint colorLoc, Ponto3d cor, int deslocamento, int quantBytes)
{
    for (int i = 0; i < quantBytes; i++)
    {
        glUniform4f(colorLoc, cor.x, cor.y, cor.z, 1);
        glDrawArrays(GL_LINE_LOOP, deslocamento + i, 2);
    }
    glBindVertexArray(0);
}
