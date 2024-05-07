#ifndef BD_GRAPHICS_HPP
#define BD_GRAPHICS_HPP

#include "BD_ResourceManager.hpp"
#include "BD_SpriteRenderer.hpp"
#include "BD_TextRenderer.hpp"
#include "BD_CodeErrors.hpp"

//Includes OpenGL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include <variant>
using std::variant;
using std::get;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct TextureRender
{
    std::string textureName;
    glm::vec2 position;
    glm::vec2 size;
    float rotate;
    glm::vec3 color;
    TextureRender(std::string _textureName, glm::vec2 _position, glm::vec2 _size, float _rotate, glm::vec3 _color) :
        textureName(_textureName), position(_position), size(_size), rotate(_rotate), color(_color){}
};

struct TextRender{
    std::string fontName;
    std::string text;
    float x;
    float y;
    float scale;
    glm::vec3 color;
    TextRender(std::string _fontName, std::string _text, float _x, float _y, float _scale, glm::vec3 _color) : 
        fontName(_fontName), text(_text), x(_x), y(_y), scale(_scale), color(_color) {}
};

using TextOrTexture = variant<TextureRender, TextRender>;

class BlueDjinn{

public:
    unsigned int ScreenWidth, ScreenHeight;
    bool Keys[1024];
    bool KeysProcessed[1024];
    bool isActive;
    GLFWwindow* window;

    int Init();
    int InitRender(); //TODO - Init e End vão se tornar um while que contemplará tudo
    int ProcessRenderList();
    int EndRender();
    bool GetKeyInput(int key);
    int ProcessInput(int key);
    int LoadAndGetShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name, std::string type);
    int LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    int GetShader(std::string name, std::string type);
    int LoadTexture(std::string file, bool alpha, std::string textureName);
    int LoadFont(std::string file, int size, std::string fontName);
    int DrawTexture(std::string textureName, glm::vec3 position, glm::vec2 size, float rotate, glm::vec3 color);
    int DrawSimpleTexture(std::string textureName, int x, int y, int z);
    int DrawAnimationTexture(std::string textureName, int x, int y, int z);
    int DrawText2D(std::string fontName, std::string text, float x, float y, float z, float scale, glm::vec3 color);
    BlueDjinn(unsigned int width, unsigned int height);
    ~BlueDjinn(); //destructor
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
private:
    std::unordered_map<std::string, SpriteRenderer*> spriteRenderers;
    glm::mat4 projection;
    SpriteRenderer  *Renderer;
    TextRenderer    *Text;
    std::vector<std::tuple<int, std::string, TextOrTexture>> RenderList;
    int CreateWindow(int screenWidth, int screenHeight);

};

#endif // BD_GRAPHICS_HPP
