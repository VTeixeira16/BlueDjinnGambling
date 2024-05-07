
#include "BD_Graphics.hpp"

using namespace std;

SpriteRenderer  *Renderer;
TextRenderer    *Text;
std::vector<std::tuple<int, std::string, TextOrTexture>> RenderList;

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
    delete Text;
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

    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;

    projection = glm::ortho(0.0f, static_cast<float>(ScreenWidth),
        static_cast<float>(ScreenHeight), 0.0f, -1.0f, 1.0f);

    return 0;
}

int BlueDjinn::CreateWindow(int screenWidth, int screenHeight)
{
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

int BlueDjinn::LoadAndGetShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name, std::string type)
{

    LoadShader(vShaderFile, fShaderFile, gShaderFile, name);
    GetShader(name, type);

    return 0;
}

int BlueDjinn::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{

    ResourceManager::LoadShader(vShaderFile, fShaderFile, gShaderFile, name);

    return 0;
}

int BlueDjinn::GetShader(std::string name, std::string type)
{

    if(type == "text"){
        ResourceManager::GetShader(name).Use().SetInteger("text", 0);
    }else{
        ResourceManager::GetShader(name).Use().SetInteger("image", 0);
    }

    ResourceManager::GetShader(name).SetMatrix4("projection", projection);
    // set render-specific controls
    Shader myShader;

    //TODO - filtrar se for sprite ou imagem
    //TODO - Estrutura atual está com o último shader sendo usado para criar um novo render sempre que esse trecho é chamado.

    myShader = ResourceManager::GetShader(name);

    if(type == "text"){
        //TODO - Avaliar usar o newTextRenderer
//        myShader.Use();
        Text = new TextRenderer(myShader);
    }else{
        Renderer = new SpriteRenderer(myShader);
    }

    return 0;
}

int BlueDjinn::LoadTexture(string file, bool alpha, string textureName)
{

    ResourceManager::LoadTexture(file, alpha, textureName);

    return 0;
}

int BlueDjinn::LoadFont(string file, int size, string fontName)
{

    Font2D teste = ResourceManager::LoadFont(file, size, fontName);

//    std::cout << "Function: " << __FUNCTION__ << " - Line: " << __LINE__ << " ID:[" << teste.ID << "] Size:[" << teste.size << "]." << std::endl;


//    Text = new TextRenderer(ScreenWidth, ScreenHeight);
//    Text->Load(file, size);

    return 0;
}

int BlueDjinn::DrawTexture(std::string textureName, glm::vec3 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    Texture2D myTexture;
    myTexture = ResourceManager::GetTexture(textureName);

    TextureRender textureRender(textureName, glm::vec2(position.x, position.y), glm::vec2(myTexture.Width * (size.x / 100), myTexture.Height * (size.y / 100)), rotate, color);

    RenderList.push_back(std::make_tuple(position.z, "image", textureRender));

    return 0;
}

int BlueDjinn::DrawSimpleTexture(std::string textureName, int x, int y, int z)
{

    Texture2D myTexture;
    myTexture = ResourceManager::GetTexture(textureName);
    glm::vec2 size = glm::vec2(myTexture.Width, myTexture.Height);
    TextureRender textureRender(textureName, glm::vec2(x, y), glm::vec2(myTexture.Width, myTexture.Height), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    RenderList.push_back(std::make_tuple(z, "image", textureRender));
    return 0;
}

int BlueDjinn::DrawAnimationTexture(std::string textureName, int x, int y, int z)
{

    return 0;
}

int BlueDjinn::DrawText2D(std::string fontName, std::string text, float x, float y, float z, float scale, glm::vec3 color)
{
    TextRender textRender(fontName, text, x, y, scale, color);

    RenderList.push_back(std::make_tuple(z, "text", textRender));

    return 0;
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

int BlueDjinn::ProcessRenderList()
{
    auto compareZIndex = [](const auto& a, const auto& b) {
        return std::get<0>(a) < std::get <0> (b);
    };

    std::sort(RenderList.begin(), RenderList.end(), compareZIndex);
    while (!RenderList.empty()) {


        auto item = RenderList.front();

        //std::cout << "NomeItem" << std::get<1>(item) << std::endl;

        if (auto* fontPtr = std::get_if<TextRender>(&std::get<2>(item))) {

            Font2D myFont;
            myFont = ResourceManager::GetFont(fontPtr->fontName);

            //std::cout << "Size:[" << myFont.size << "]" << std::endl;
            //std::cout << "Function: " << __FUNCTION__ << " - Line: " << __LINE__ << " ID:[" << myFont.ID << "] Size:[" << myFont.size << "]." << std::endl;

            Text->RenderText(myFont, fontPtr->text, fontPtr->x, fontPtr->y, fontPtr->scale, fontPtr->color);
        }
        else if (auto* texturePtr = std::get_if<TextureRender>(&std::get<2>(item))) {

            Texture2D myTexture;
            myTexture = ResourceManager::GetTexture(texturePtr->textureName);

            Renderer->DrawSprite(myTexture, glm::vec2(texturePtr->position.x, texturePtr->position.y), texturePtr->size, texturePtr->rotate, texturePtr->color);
        }


        RenderList.erase(RenderList.begin());

    }

    return 0;
}

int BlueDjinn::EndRender()
{
    ProcessRenderList();

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

int BlueDjinn::ProcessInput(int key)
{

//    if (this->Keys[key] == true)
//    {
        std::cout << "Key " << key << "foi pressionada." << std::endl;

//    }

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool BlueDjinn::GetKeyInput(int key)
{

    int ret = false;

    if (this->Keys[key] == true)
    {
        std::cout << "Key " << key << "foi pressionada." << std::endl;
        return true;
    }

    return ret;
}

static void static_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
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
        std::cout << "Key " << key << "foi pressionada." << std::endl;
    }

    if (action == GLFW_PRESS)
        Keys[key] = true;
    else if (action == GLFW_RELEASE)
    {
        BlueDjinn::Keys[key] = false;
        BlueDjinn::KeysProcessed[key] = false;
    }
}

