
#include "BD_Graphics.hpp"

using namespace std;

SpriteRenderer  *Renderer;

//GLFW Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
static void static_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);



BlueDjinn::BlueDjinn(unsigned int width, unsigned int height)
    : ScreenWidth(width), ScreenHeight(height)
{

}

BlueDjinn::~BlueDjinn(){
    //TODO - Destructor
    delete Renderer;
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


    glfwSetWindowUserPointer(window, this); //Avaliar necessidade
    glfwSetKeyCallback(window, static_key_callback);


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

int BlueDjinn::ProcessInput(int key){

//    if (this->Keys[key] == true)
//    {
//        std::cout << "Key " << key << "foi pressionada." << std::endl;

//    }

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool BlueDjinn::GetKeyInput(int key){

    int ret = false;

    if (this->Keys[key] == true)
    {
        std::cout << "Key " << key << "foi pressionada." << std::endl;
        return true;
    }

    return ret;
}

static void static_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    BlueDjinn* instance = static_cast<BlueDjinn*>(glfwGetWindowUserPointer(window));
    if (instance) {
        instance->key_callback(window, key, scancode, action, mode);
    }
}

void BlueDjinn::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        std::cout << "Key:[" << key << std::endl;
    }

    if (action == GLFW_PRESS)
        Keys[key] = true;
    else if (action == GLFW_RELEASE)
    {
        BlueDjinn::Keys[key] = false;
        BlueDjinn::KeysProcessed[key] = false;
    }
}

