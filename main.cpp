#include "BD_Graphics.hpp"
#include "BD_Curl.hpp"

#include <iostream>
#include "texture.h"
//    ResourceManager resourceManager;

BlueDjinn blueDjinn(1920,1080);


int main(){

    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;

//    verificarAPI("https://localhost:7013/api/LoginData/1");
//    verificarAPI("https://localhost:7013/api/LoginData/2");
//    verificarAPI("https://localhost:7013/api/LoginData/3");

    blueDjinn.Init();

    blueDjinn.LoadAndGetShader("shaders/defaultVS.glsl", "shaders/defaultFS.glsl", nullptr, "sprite");
    blueDjinn.LoadTexture("resources/textures/awesomeface.png", true, "sprite");
    blueDjinn.LoadTexture("resources/textures/impacta.png", true, "impacta");

//    blueDjinn.GetShader("sprite");
//    blueDjinn.LoadTexture("resources/textures/awesomeface.png", true, "sprite", "sprite");

//    blueDjinn.GetShader("impacta");
//    blueDjinn.LoadTexture("resources/textures/impacta.png", true, "impacta", "impacta");

//    blueDjinn.GetShader("sprite");


    //Terá uma função na main para carregar as imagens
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;


    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;


    while (!blueDjinn.isActive){
        blueDjinn.InitRender();

        blueDjinn.DrawTexture("sprite", glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        blueDjinn.DrawTexture("impacta", glm::vec2(0, 0), glm::vec2(300, 400), 0.0f, glm::vec3(0.5f, 0.5f, 0.5f));


        blueDjinn.EndRender();
    }
    glfwTerminate();
    std::cout << "Final do programa" << std::endl;

    return 0;
}
