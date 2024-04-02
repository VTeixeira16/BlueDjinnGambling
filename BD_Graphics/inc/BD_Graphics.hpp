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
    bool isActive;
    GLFWwindow* window;

    int Init();
    int InitRender();
    int EndRender();
    int LoadAndGetShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    int LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    int GetShader(std::string name);
    int LoadTexture(std::string file, bool alpha, std::string textureName);
    int DrawTexture(std::string textureName, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
    BlueDjinn(unsigned int width, unsigned int height);
    ~BlueDjinn(); //destructor
private:
    std::unordered_map<std::string, SpriteRenderer*> spriteRenderers;
    glm::mat4 projection;
    SpriteRenderer  *Renderer;
    CreateWindow(int screenWidth, int screenHeight);

};

#endif // BD_GRAPHICS_HPP
