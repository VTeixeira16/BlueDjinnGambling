
#include "BD_Graphics.hpp"

using namespace std;

SpriteRenderer  *Renderer;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Avaliar possibilidade de mudar para classe BD_Graphics

BlueDjinn::BlueDjinn(unsigned int width, unsigned int height)
    : ScreenWidth(width), ScreenHeight(height)
{

}

BlueDjinn::~BlueDjinn(){
    //TODO - Destructor
}

int BlueDjinn::Init()
{

    cout << "BD GRAPHICS Inicializada" << endl;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

//////////////////////////////
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
    BlueDjinn::CreateWindow(ScreenWidth, ScreenHeight);
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;

    projection = glm::ortho(0.0f, static_cast<float>(ScreenWidth),
        static_cast<float>(ScreenHeight), 0.0f, -1.0f, 1.0f);

    return 0;
}

int BlueDjinn::CreateWindow(int screenWidth, int screenHeight){
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

int BlueDjinn::LoadAndGetShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name){

    LoadShader(vShaderFile, fShaderFile, gShaderFile, name);
    GetShader(name);

    return 0;
}

int BlueDjinn::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name){

    ResourceManager::LoadShader(vShaderFile, fShaderFile, gShaderFile, name);

    return 0;
}

int BlueDjinn::GetShader(std::string name){

    ResourceManager::GetShader(name).Use().SetInteger("image", 0);
    ResourceManager::GetShader(name).SetMatrix4("projection", projection);
    // set render-specific controls
    Shader myShader;
    myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);

    return 0;
}

int BlueDjinn::LoadTexture(string file, bool alpha, string textureName){

    ResourceManager::LoadTexture(file, alpha, textureName);

    return 0;
}

int BlueDjinn::DrawTexture(std::string textureName, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color){

    Texture2D myTexture;
    myTexture = ResourceManager::GetTexture(textureName);
    Renderer->DrawSprite(myTexture, position, size, rotate, color);
}




int BlueDjinn::InitRender()
{
    // input
    // -----
    isActive = glfwWindowShouldClose(window);

    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------


    return 0;
}

int BlueDjinn::EndRender(){
    glfwSwapBuffers(window);
    glfwPollEvents();

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
