#include "BD_Graphics.hpp"
#include "BD_Curl.hpp"

#include <iostream>
#include "texture.h"
//    ResourceManager resourceManager;

BlueDjinn blueDjinn(1920,1080);


void BlueDjinn_GraphicCore_Render(){
//    cout << "Renderizando" << endl;
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
}

int main(){

    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;

//    verificarAPI("https://localhost:7013/api/LoginData/1");
//    verificarAPI("https://localhost:7013/api/LoginData/2");
//    verificarAPI("https://localhost:7013/api/LoginData/3");

    blueDjinn.Init();

    blueDjinn.LoadAndGetShader("shaders/defaultVS.glsl", "shaders/defaultFS.glsl", nullptr, "sprite");
    blueDjinn.LoadTexture("resources/textures/awesomeface.png", true, "sprite");
    blueDjinn.LoadTexture("resources/textures/impacta.png", true, "impacta");
    blueDjinn.LoadTexture("resources/textures/container.jpg", false, "container");

    //Terá uma função na main para carregar as imagens
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;


    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;



    while (!blueDjinn.isActive){

        blueDjinn.InitRender();

        blueDjinn.DrawTexture("container", glm::vec2(800, 800), glm::vec2(400, 220), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

////        if(blueDjinn.GetKeyInput(GLFW_KEY_A)){
//            blueDjinn.DrawTexture("sprite", glm::vec2(200, 200), glm::vec2(300, 400), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
////        }
////        if(blueDjinn.GetKeyInput(GLFW_KEY_S)){
//            blueDjinn.DrawTexture("impacta", glm::vec2(0, 0), glm::vec2(400, 125), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
////        }
////        if(blueDjinn.GetKeyInput(GLFW_KEY_D)){
//            blueDjinn.DrawSimpleTexture("container", 405, 0);
////        }


        blueDjinn.DrawSimpleTexture("container", 800, 800);
        blueDjinn.DrawSimpleTexture("sprite", 200, 200);
        blueDjinn.DrawSimpleTexture("impacta", 0, 0);



        blueDjinn.EndRender();
    }
    glfwTerminate();
    std::cout << "Final do programa" << std::endl;

    return 0;
}
