#ifndef BD_RESOURCE_MANAGER_HPP
#define BD_RESOURCE_MANAGER_HPP

#include <string>
#include <map>
//#include "stb_image.h"

#include "BD_Texture.hpp"
#include "BD_Shader.hpp"
#include "BD_Font.hpp"
#include "BD_TextRenderer.hpp"

class ResourceManager{
public:
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Font2D>    Fonts;

    static Texture2D LoadTexture(std::string file, bool alpha, std::string name);
    static Texture2D GetTexture(std::string name);
    static Font2D    LoadFont(std::string file, unsigned int size, std::string name);
    static Font2D    GetFont(std::string name);

    static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    static Shader    &GetShader(std::string name);

//    ResourceManager();

private:
    ResourceManager() { }
    static Texture2D loadTextureFromFile(std::string file, bool alpha);
    static Font2D    loadFontFromFile(std::string file, unsigned int size);
    static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

};

#endif //BD_RESOURCE_MANAGER_HPP
