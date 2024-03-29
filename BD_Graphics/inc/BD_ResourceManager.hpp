#ifndef BD_RESOURCE_MANAGER_HPP
#define BD_RESOURCE_MANAGER_HPP

#include <string>
#include <map>
//#include "stb_image.h"

#include "texture.h"
#include "BD_Shader.h"


class ResourceManager{
public:
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, Shader>    Shaders;

    static Texture2D LoadTexture(std::string file, bool alpha, std::string name);
    static Texture2D GetTexture(std::string name);
    static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    static Shader    GetShader(std::string name);

//    ResourceManager();

private:
    ResourceManager() { }
    static Texture2D loadTextureFromFile(std::string file, bool alpha);
    static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

};

#endif //BD_RESOURCE_MANAGER_HPP
