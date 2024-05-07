#include "BD_Graphics.hpp"
#include "BD_Curl.hpp"

#include <iostream>
//#include "BD_Texture.hpp"

BlueDjinn blueDjinn(1920,1080);
int main(){

    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;

    //verificarAPI("https://localhost:7013/api/LoginData/1");
//     verificarAPI("https://localhost:7013/api/LoginData/2");
//    verificarAPI("https://localhost:7013/api/LoginData/3");

    blueDjinn.Init();
    blueDjinn.LoadAndGetShader("shaders/defaultVS.glsl", "shaders/defaultFS.glsl", nullptr, "sprite", "image");
    blueDjinn.LoadAndGetShader("shaders/textVS.glsl", "shaders/textFS.glsl", nullptr, "text", "text");

////    blueDjinn.LoadShader("shaders/textVS.glsl", "shaders/textFS.glsl", nullptr, "text");
////    blueDjinn.GetShader("shaders/textVS.glsl", "shaders/textFS.glsl", nullptr, "text");
    blueDjinn.LoadTexture("resources/textures/awesomeface.png", true, "sprite");
    blueDjinn.LoadTexture("resources/textures/impacta.png", true, "impacta");
    blueDjinn.LoadTexture("resources/textures/container.jpg", false, "container");

    blueDjinn.LoadFont("resources/fonts/OCRAEXT.ttf", 64, "fontA_64");

    blueDjinn.LoadFont("resources/fonts/Antonio-Bold.ttf", 32, "fontA_32");


    //Terá uma função na main para carregar as imagens
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;



    while (!blueDjinn.isActive){

        blueDjinn.InitRender();

//        blueDjinn.DrawTexture("container", glm::vec2(800, 800), glm::vec2(400, 220), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

////        if(blueDjinn.GetKeyInput(GLFW_KEY_A)){
////        }
////        if(blueDjinn.GetKeyInput(GLFW_KEY_S)){
//            blueDjinn.DrawTexture("impacta", glm::vec2(0, 0), glm::vec2(400, 125), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
////        }
////        if(blueDjinn.GetKeyInput(GLFW_KEY_D)){
//            blueDjinn.DrawSimpleTexture("container", 405, 0);
////        }
///
///


//        blueDjinn.DrawText2D("fontA_32", "FonteB", 200, 400, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));


        if(blueDjinn.GetKeyInput(GLFW_KEY_A)){
            blueDjinn.DrawTexture("sprite", glm::vec3(200, 200, 70), glm::vec2(100, 100), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        }

        blueDjinn.DrawSimpleTexture("container", 0, 0, 4);
        blueDjinn.DrawSimpleTexture("sprite", 100, 100, 50);
        blueDjinn.DrawSimpleTexture("impacta", 200, 200, 10);
        blueDjinn.DrawSimpleTexture("container", 300, 300, 0);
//        Shader shader = ResourceManager::GetShader("text");

//        std::cout << "ID DO SHADER " << shader.ID << std::endl;

//        std::string fontName, std::string text, float x, float y, float scale, glm::vec3 color

        blueDjinn.DrawText2D("fontA_64", "FonteA", 200, 400, 90, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        blueDjinn.DrawText2D("fontA_32", "FonteB", 200, 400, 30, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        blueDjinn.DrawText2D("fontA_64", "FonteA", 200, 600, 0, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        blueDjinn.DrawText2D("fontA_32", "FonteB", 200, 600, 2, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));




        blueDjinn.EndRender();
    }
    glfwTerminate();
    std::cout << "Final do programa" << std::endl;

    return 0;
}
