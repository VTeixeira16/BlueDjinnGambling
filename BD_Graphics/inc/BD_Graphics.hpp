#ifndef BD_GRAPHICS_HPP
#define BD_GRAPHICS_HPP

#include "BD_ResourceManager.hpp"
#include "BD_SpriteRenderer.hpp"
#include "BD_CodeErrors.hpp"

//Includes OpenGL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BlueDjinn{

public:
    unsigned int ScreenWidth, ScreenHeight;
    bool Keys[1024];
    bool KeysProcessed[1024];
    bool isActive;
    GLFWwindow* window;

    int Init();
    int InitRender(); //TODO - Init e End vão se tornar um while que contemplará tudo
    int EndRender();
    bool GetKeyInput(int key);
    int ProcessInput(int key);
    int LoadAndGetShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    int LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    int GetShader(std::string name);
    int LoadTexture(std::string file, bool alpha, std::string textureName);
    int DrawTexture(std::string textureName, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
    BlueDjinn(unsigned int width, unsigned int height);
    ~BlueDjinn(); //destructor
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
private:
    std::unordered_map<std::string, SpriteRenderer*> spriteRenderers;
    glm::mat4 projection;
    SpriteRenderer  *Renderer;
    int CreateWindow(int screenWidth, int screenHeight);

};

#endif // BD_GRAPHICS_HPP
