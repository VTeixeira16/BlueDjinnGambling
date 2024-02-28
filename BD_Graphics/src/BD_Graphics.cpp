#include <iostream>
#include "BD_Graphics.hpp"

//Includes OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int teste(){
    cout << "BD GRAPHICS Inicializada" << endl;
    return 0;
}

int BD_Graphics_Teste()
{
    cout << __FUNCTION__ << " " << __LINE__ << endl;

    //Inicia GLFW e configura
    if(glfwInit() == GLFW_FALSE){
        cout << __func__ << " glfwInit ERROR." << endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    //Cria janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Posicao no contexto openGL
    glViewport(0, 0, 800, 600);

    //Callback abaixo é chamado sempre que a janela for ajustada
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //Laço que controla a janela
    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //Comandos de renderização
        glClearColor(0.2f, 0.7f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //checa e chama eventos e troca(swap) os buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }


    //Limpa/deleta todos os recursos GLFW alocados
    glfwTerminate();
    cout << "Aplicação encerrada" << endl;
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
