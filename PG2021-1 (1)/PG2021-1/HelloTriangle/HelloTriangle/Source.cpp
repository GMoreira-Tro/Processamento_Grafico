#include <iostream>
#include <string>
#include <conio.h>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

using namespace std;

/*
Estrutura de ponto bidimensional.
*/
struct Ponto2d
{
public:
    float x;
    float y;

    Ponto2d(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};
/*
Estrutura de ponto tridimensional.
*/
struct Ponto3d
{
public:
    float x;
    float y;
    float z;

    Ponto3d(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar* vertexShaderSource = "#version 450\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

//Códifo fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar* fragmentShaderSource = "#version 450\n"
"uniform vec4 inputColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = inputColor;\n"
"}\n\0";

GLuint colorLoc, shaderID;

const Ponto3d corDeFundo = Ponto3d(0.5f, 0.5f, 0.5f);

const float DEG2RAD = 180. / 3.14159265358979323846f;
const float RAD2DEG = 3.14159265358979323846f / 180.;

void exercicio1();
void exercicio2();
void exercicio3();
void exercicio4();
void exercicio5();
void exercicio6();
void exercicio7();
int setupShader();
int setupGeometry(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3);

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
        GLFWwindow* window = glfwCreateWindow(1920, 1080, "Ola Triangulo!", nullptr, nullptr);
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

        // Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Compilando e buildando o programa de shader
        shaderID = setupShader();

        // Enviando a cor desejada (vec4) para o fragment shader
        // Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
        // que não está nos buffers
        GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
        assert(colorLoc > -1);
        glUseProgram(shaderID);

        //Loop da aplicação da janela.
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
            case '4':
                exercicio4();
                break;
            case '5':
                exercicio5();
                break;
            case '7':
                exercicio7();
                break;
            default:
                glfwSetWindowShouldClose(window, GL_TRUE);
                cout << "\n\nEsse exercício não tem :(";
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

//Esta função está basntante hardcoded - objetivo é compilar e "buildar" um programa de
// shader simples e único neste exemplo de código
// O código fonte do vertex e fragment shader está nos arrays vertexShaderSource e
// fragmentShader source no iniçio deste arquivo
// A função retorna o identificador do programa de shader
int setupShader()
{
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Checando erros de compilação (exibição via log no terminal)
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Checando erros de compilação (exibição via log no terminal)
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Linkando os shaders e criando o identificador do programa de shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Checando por erros de linkagem
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Esta função está bastante harcoded - objetivo é criar os buffers que armazenam a 
// geometria de um triângulo
// Apenas atributo coordenada nos vértices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A função retorna o identificador do VAO
int setupGeometry(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3)
{
    // Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
    // sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
    // Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
    // Pode ser arazenado em um VBO único ou em VBOs separados
    GLfloat vertices[] = {
        vertice1.x, vertice1.y, 0.0,
         vertice2.x, vertice2.y, 0.0,
         vertice3.x, vertice3.y, 0.0,
    };

    GLuint VBO, VAO;

    //Geração do identificador do VBO
    glGenBuffers(1, &VBO);
    //Faz a conexão (vincula) do buffer como um buffer de array
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Envia os dados do array de floats para o buffer da OpenGl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Geração do identificador do VAO (Vertex Array Object)
    glGenVertexArrays(1, &VAO);
    // Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
    // e os ponteiros para os atributos 
    glBindVertexArray(VAO);
    //Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
    // Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
    // Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
    // Tipo do dado
    // Se está normalizado (entre zero e um)
    // Tamanho em bytes 
    // Deslocamento a partir do byte zero 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
    // atualmente vinculado - para que depois possamos desvincular com segurança
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
    glBindVertexArray(0);

    return VAO;
}

/*
Imprime um triângulo de acordo com os vértices.
@param vertice1 Primeiro vértice.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
@param cor Cor do triângulo.
*/
void desenhaTriangulo(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor)
{
    //Jeito mais 'simples', mas menos interesssante
    //glBegin(GL_TRIANGLES);
    //glVertex2f(vertice1.x, vertice1.y);
    //glVertex2f(vertice2.x, vertice2.y);
    //glVertex2f(vertice3.x, vertice3.y);
    //glUniform4f(colorLoc, 0.6f, 0.0f, 0.6f, 0);
    //glEnd();

    GLuint VAO = setupGeometry(vertice1, vertice2, vertice3);
    glUniform4f(colorLoc, cor.x, cor.y, cor.z, 1.0f);
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*
Imprime um triângulo de acordo com os vértices.
@param vertice1 Primeiro vértice.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
@param cor Cor do triângulo.
@param contorno Contorno do triângulo
*/
void desenhaTrianguloComContorno(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d cor, Ponto3d contorno)
{
    //Desenho do triângulo
    //GL_TRIANGLES - preenchimento do triângulo
    GLuint VAO = setupGeometry(vertice1, vertice2, vertice3);
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
@param vertice1 Primeiro vértice.
@param vertice2 Segundo vértice.
@param vertice3 Terceiro vértice.
@param contorno Contorno do triângulo
*/
void desenhaTrianguloSemFundo(Ponto2d vertice1, Ponto2d vertice2, Ponto2d vertice3, Ponto3d contorno)
{
    desenhaTrianguloComContorno(vertice1, vertice2, vertice3,
        Ponto3d(corDeFundo.x, corDeFundo.y, corDeFundo.z), contorno);
}

/*
Imprime um círculo de acordo com um ponto inicial.
@param pontoInicial Ponto central do círculo.
@param cor Cor do círculo.
@param fatorDeEscala Fator de escala para multiplicar o círculo.
*/
void desenhaCirculo(Ponto2d pontoInicial, Ponto3d cor, float fatorDeEscala)
{
    for (int i = 0; i < 360; i++)
    {
        float angle = i * RAD2DEG;
        float postAngle = (i + 1) * RAD2DEG;

        desenhaTriangulo(Ponto2d(pontoInicial.x, pontoInicial.y),
            Ponto2d(sin(angle) * fatorDeEscala + pontoInicial.x, cos(angle) * fatorDeEscala + pontoInicial.y),
            Ponto2d(sin(postAngle) * fatorDeEscala + pontoInicial.x, cos(postAngle) * fatorDeEscala + pontoInicial.y),
            Ponto3d(cor.x, cor.y, cor.z));
    }
}

void exercicio1()
{
    desenhaTriangulo(Ponto2d(-0.5, -0.5f), Ponto2d(-0.05f, -0.5f), Ponto2d(-0.05f, 0.5f), Ponto3d(1,0,0));
    desenhaTriangulo(Ponto2d(0.5, -0.5f), Ponto2d(0.05f, -0.5f), Ponto2d(0.05f, 0.5f), Ponto3d(0,0,1));
}

void exercicio2()
{
    desenhaTrianguloComContorno(Ponto2d(-0.5, -0.5f), Ponto2d(-0.05f, -0.5f), Ponto2d(-0.05f, 0.5f), 
        Ponto3d(1, 0, 0), Ponto3d(0,1,0));
    desenhaTriangulo(Ponto2d(0.5, -0.5f), Ponto2d(0.05f, -0.5f), Ponto2d(0.05f, 0.5f), Ponto3d(0, 0, 1));
    desenhaTrianguloSemFundo(Ponto2d(0.6, -0.5f), Ponto2d(0.8f, -0.5f), Ponto2d(0.625f, 0),
        Ponto3d(0, 1, 0));
}

void exercico3()
{

}

void exercicio4()
{
    desenhaTriangulo(Ponto2d(-0.5, -0.5f), Ponto2d(-0.05f, -0.5f), Ponto2d(-0.05f, 0.5f), Ponto3d(0.4f, 0, 0.4f));
    desenhaTriangulo(Ponto2d(-0.5, -0.5f), Ponto2d(-0.05f, 0.5f), Ponto2d(-0.5f, 0.5f), Ponto3d(0.4f, 0, 0.4f));
}

void exercicio5()
{
    desenhaCirculo(Ponto2d(0, 0), Ponto3d(1, 1, 0), 0.5f);
}

void exercicio6()
{

}

void exercicio7()
{
    desenhaCirculo(Ponto2d(0, 0), Ponto3d(0.8f,0.8f,0) ,0.5f);
    desenhaTriangulo(Ponto2d(-0.3f, -0.1f), Ponto2d(0.3f, -0.1f), Ponto2d(0, -0.3f), Ponto3d(0.8f, 0, 0));
    desenhaTriangulo(Ponto2d(-0.3f, 0.1f), Ponto2d(-0.1f, 0.1f), Ponto2d(-0.2f, 0.3f), Ponto3d(0, 0.8f, 0));
    desenhaTriangulo(Ponto2d(0.1f, 0.1f), Ponto2d(0.3f, 0.1f), Ponto2d(0.2f, 0.3f), Ponto3d(0, 0, 0.8f));
    desenhaTriangulo(Ponto2d(0.75f, 0.5f), Ponto2d(0, 0.75f), Ponto2d(-0.75f, 0.5f), Ponto3d(0.7f, 0.7f, 0.7f));
}