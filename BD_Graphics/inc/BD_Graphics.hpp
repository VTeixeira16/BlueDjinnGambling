#ifndef BD_GRAPHICS_HPP
#define BD_GRAPHICS_HPP

#include "BD_ResourceManager.hpp"
#include "BD_SpriteRenderer.hpp"
#include "BD_CodeErrors.hpp"
#include "BD_Game.hpp"

//Includes OpenGL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BlueDjinn{

public:
    unsigned int ScreenWidth, ScreenHeight;
    bool isActive;
    GLFWwindow* window;

    int Init();
    int Render();
    BlueDjinn(unsigned int width, unsigned int height);
    ~BlueDjinn(); //destructor
private:
    CreateWindow(int screenWidth, int screenHeight);

};

#endif // BD_GRAPHICS_HPP
