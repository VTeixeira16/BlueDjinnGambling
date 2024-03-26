#include "BD_Graphics.hpp"
#include "BD_Curl.hpp"

#include <iostream>
#include "texture.h"
//    ResourceManager resourceManager;

BlueDjinn blueDjinn(800,600);


int main(){

    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;

//    verificarAPI("https://localhost:7013/api/LoginData/1");
//    verificarAPI("https://localhost:7013/api/LoginData/2");
//    verificarAPI("https://localhost:7013/api/LoginData/3");

    blueDjinn.Init();

    //Terá uma função na main para carregar as imagens
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;


    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;


    while (!blueDjinn.isActive){
        blueDjinn.Render();
//        game.Render();
    }
    glfwTerminate();
    std::cout << "Final do programa" << std::endl;

    return 0;
}
