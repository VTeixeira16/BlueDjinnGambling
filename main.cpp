#include "BD_Graphics.hpp"
#include "BD_Core.hpp"

#include <iostream>
#include "texture.h"
//    ResourceManager resourceManager;

BlueDjinn blueDjinn(800,600);

int main(){

    BD_CURL_ST BD_curlRequisition;

    BD_curlRequisition.url = "https://openai.com";

//    BD_Core_teste();
//    BD_Core_curl_get(BD_curlRequisition.url);
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;

//    Texture2D texture;


    blueDjinn.Init();
//    BD_Graphics_BindTexture();
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "awesomeface");
//    std::cout << "Carregou primeira textura" << std::endl;
//    ResourceManager::LoadTexture("resources/textures/container.jpg", true, "container");
//    BD_Graphics_GenerateTexture("resources/textures/awesomeface.png");
//    BD_Graphics_GenerateTexture("resources/textures/container.jpg");

//    BD_Graphics_Render2D();

//    blueDjinn.Render();

    while (!blueDjinn.isActive){
        blueDjinn.Render();
    }
    glfwTerminate();
    std::cout << "Final do programa" << std::endl;

    return 0;
}
