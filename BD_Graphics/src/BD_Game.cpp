#include "BD_Game.hpp"
#include "BD_SpriteRenderer.hpp"

SpriteRenderer  *Renderer;

Game::Game(unsigned int width, unsigned int height)
    : Width(width), Height(height)
{

}

void Game::Init()
{

    // load shaders
    ResourceManager::LoadShader("shaders/defaultVS.glsl", "shaders/defaultFS.glsl", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls

    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
//    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "face");
}

void Game::Render()
{
    Texture2D texture = ResourceManager::GetTexture("face");
    Renderer->DrawSprite(texture,
        glm::vec2(0.0f, 0.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    Renderer->DrawSprite(texture,
        glm::vec2(301.0f, 0.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
