#include "BD_Graphics.hpp"
#include "BD_Curl.hpp"

#include <iostream>

#include <random>
#include <time.h>
//#include "BD_Texture.hpp"

BlueDjinn blueDjinn(1920,1080);

#define MACHINE_NAME "TCC_DESKTOP_WINDOWS_12"

enum GAME_STATE {
    ST_IDLE,
    ST_INIT_PLAY,
    ST_PLAYING,
    ST_ENDGAME
};

const char *formatData(){
    char currentDateTime[24] = {0};

    time_t currentTime;
    time(&currentTime);

    // Converte o tempo atual para uma estrutura tm
    struct tm *localTime = localtime(&currentTime);

    // Extrai as informações de data e hora
    int year = localTime->tm_year + 1900; // tm_year é o número de anos desde 1900
    int month = localTime->tm_mon + 1;    // tm_mon é o número de meses desde janeiro (0-11)
    int day = localTime->tm_mday;         // Dia do mês (1-31)
    int hour = localTime->tm_hour;        // Hora do dia (0-23)
    int minute = localTime->tm_min;       // Minuto (0-59)
    int second = localTime->tm_sec;       // Segundo (0-59)

    sprintf(currentDateTime, "%04d-%02d-%02dT%02d:%02d:%02d.001Z", year, month, day, hour, minute, second);
    std::cout << "HORA ATUAL(currentDateTime): " << currentDateTime << std::endl;

    // "2024-04-22T21:46:44.411Z"

    return strdup(currentDateTime);

}

int LoadData() {

    blueDjinn.Init();

    blueDjinn.LoadAndGetShader("shaders/defaultVS.glsl", "shaders/defaultFS.glsl", nullptr, "sprite", "image");
    blueDjinn.LoadAndGetShader("shaders/textVS.glsl", "shaders/textFS.glsl", nullptr, "text", "text");

    blueDjinn.LoadTexture("resources/textures/cartela.png", true, "cartela");
    blueDjinn.LoadTexture("resources/textures/fundoCartela.png", true, "fundoCartela");


    //blueDjinn.LoadFont("resources/fonts/OCRAEXT.ttf", 64, "fontA_64");
    blueDjinn.LoadFont("resources/fonts/Antonio-Bold.ttf", 72, "fontContador");
    blueDjinn.LoadFont("resources/fonts/Antonio-Bold.ttf", 72, "fontA_72");
    blueDjinn.LoadFont("resources/fonts/Antonio-Bold.ttf", 50, "fontA_50");



    //Terá uma função na main para carregar as imagens
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;


    return 0;
}

int main(){

    verificarAPI("https://localhost:7013/api/LoginData/1", CURL_GET, "");
    realizarSolicitacaoHTTP("https://example.com", "GET", "");



    LoadData();
    std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
//    verificarAPI("https://localhost:7013/api/LoginData/1", CURL_GET, NULL);

//    verificarAPI("https://localhost:7013/api/LoginData/3");


    //Card Position Data
    glm::vec2 cardPosition = glm::vec2(110, 110);
    glm::vec2 ballsPosition = glm::vec2(50, 700);
    std::vector<unsigned int> cardRow = { 90, 340, 590, 840, 1090 };
    std::vector<unsigned int> cardLine = { 70, 270, 470 };

    glm::vec3 colorDefault  = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 colorMarked = glm::vec3(1.0f, 0.0f, 0.0f);

    GAME_STATE gameState = ST_IDLE;

    std::vector<unsigned int> cardNumbers = { 1,2,3,4,50,6,7,8,9,10,11,12,13,14,15 };
    std::vector<unsigned int> ballSorted(60);
    std::vector<bool> cardMarked(15);
    int countNumbers = 0;

    //Random in CPP
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 60);

    //TODO - REMOVER
    for (int i = 0; i < ballSorted.size(); i++) {
        ballSorted[i] = dis(gen);
    }

    //BD_Core_curl_get("https://localhost:7013/api/LoginData/1");



    while (!blueDjinn.isActive){

        switch (gameState)
        {
        case ST_IDLE:
            if (blueDjinn.GetKeyInput(GLFW_KEY_ENTER) || blueDjinn.GetKeyInput(GLFW_KEY_KP_ENTER)) {
                gameState = ST_INIT_PLAY;
            }
            break;
        case ST_INIT_PLAY:
            countNumbers = 0;
            for (int i = 0; i < cardNumbers.size(); i++) {
                cardMarked[i] = false;
                cardNumbers[i] = dis(gen);

            }
            for (int i = 0; i < ballSorted.size(); i++) {
                ballSorted[i] = dis(gen);
            }
            std::sort(std::begin(cardNumbers), std::end(cardNumbers));
            //TODO - Remover depois
            std::sort(std::begin(ballSorted), std::end(ballSorted));
            gameState = ST_PLAYING;
            break;
        case ST_PLAYING:
            //Verfica se número sorteado tem na cartela
            for (int i = 0; i < ballSorted.size(); i++) {
                for (int j = 0; j < cardNumbers.size(); j++) {

                    if (ballSorted[i] == cardNumbers[j]) {
                        std::string countText = "Valor do ballSorted[i]: " + std::to_string(ballSorted[i]) + " - Valor do cardNumbers[j]: " + std::to_string(cardNumbers[j]);
                        std::cout << countText << std::endl;
                        countNumbers++;
                        cardMarked[j] = true;
                        //break;
                    }
                }
            }
            gameState = ST_ENDGAME;
            break;
        case ST_ENDGAME:
            if (blueDjinn.GetKeyInput(GLFW_KEY_SPACE)) {
                const char *currentTime = formatData();
                std::cout << "HORA ATUAL: " << currentTime << std::endl;
                char body[26] = {0};
                sprintf(body, "{ \"machineName\": \"%s\", \"dateTimePlay\": \"%s\", \"hitsTotal\": %i}", MACHINE_NAME, currentTime, countNumbers);
                verificarAPI("https://localhost:7013/api/HitsNumber", CURL_POST, body);
                gameState = ST_IDLE;
            }
            break;
        default:
            break;
        }


        blueDjinn.InitRender();

        
        std::string countText = "Contador: " + std::to_string(countNumbers);
        blueDjinn.DrawText2D("fontContador", countText, 0, 0, 2, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));



        //blueDjinn.DrawSimpleTexture("container", 0, 0, 4);
//        blueDjinn.DrawTexture("fundoCartela", glm::vec3(cardPosition.x - 10, cardPosition.y - 10, 0), glm::vec2(102, 103), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        blueDjinn.DrawSimpleTexture("fundoCartela", cardPosition.x, cardPosition.y, 0);
        blueDjinn.DrawSimpleTexture("cartela", cardPosition.x, cardPosition.y, 1);

        //blueDjinn.DrawSimpleTexture("impacta", 200, 200, 10);
        //blueDjinn.DrawSimpleTexture("container", 300, 300, 0);
        int i = 0;
        for (int l = 0; l < cardLine.size(); l++) {
            for (int r = 0; r < cardRow.size(); r++){
                std::string numbString = std::to_string(cardNumbers[i]);
                blueDjinn.DrawText2D("fontA_72", numbString, cardPosition.x + cardRow[r], cardPosition.y + cardLine[l], 2, 1.0f, cardMarked[i] == true ? colorMarked : colorDefault);
                i++;
            }
        }
        
        int ballX = 0;
        int ballY = 0;
        for (int j = 0; j < ballSorted.size(); j++){ 
            std::string numbString = std::to_string(ballSorted[j]);
            //Divide bolas sorteadas em 2 linhas
            if (j < ballSorted.size() / 2) {
                blueDjinn.DrawText2D("fontA_50", numbString, ballsPosition.x + (j * 55), ballsPosition.y, 2, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
            } else {
                blueDjinn.DrawText2D("fontA_50", numbString, ballsPosition.x + ((j - ballSorted.size() / 2) * 55), ballsPosition.y + 60, 2, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }


        //blueDjinn.DrawText2D("fontA_32", "FonteB", 200, 400, 30, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        //blueDjinn.DrawText2D("fontA_64", "FonteA", 200, 600, 0, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        //blueDjinn.DrawText2D("fontA_32", "FonteB", 200, 600, 2, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));



        blueDjinn.EndRender();
    }
    glfwTerminate();
    std::cout << "Final do programa" << std::endl;

    return 0;
}
