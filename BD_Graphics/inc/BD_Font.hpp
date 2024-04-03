#ifndef BD_FONT_HPP
#define BD_FONT_HPP

#include <iostream>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

//#include "BD_TextRenderer.hpp"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class Font2D{
public:
    std::map<char, Character> Characters;

    unsigned int ID;
    unsigned int size;
    Font2D();
    void Generate(std::string font, unsigned int fontSize);
    void Bind() const;

private:


};


#endif //BD_FONT_HPP
