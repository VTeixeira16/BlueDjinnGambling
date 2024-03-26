//TODO - Vai migrar para o BD_Graphics depois

#ifndef BD_GAME_HPP
#define BD_GAME_HPP

#include "BD_SpriteRenderer.hpp"
#include "BD_ResourceManager.hpp"

class Game{
public:
    unsigned int            Width, Height;

    Game(unsigned int width, unsigned int height);
//    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    void Render();
private:

};
#endif //BD_GAME_HPP
