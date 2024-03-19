#ifndef BD_RESOURCE_MANAGER_HPP
#define BD_RESOURCE_MANAGER_HPP

#include <string>
#include <map>
//#include "stb_image.h"

#include "texture.h"

#endif //BD_RESOURCE_MANAGER_HPP


class ResourceManager{
public:
    static std::map<std::string, Texture2D> Textures;
    static Texture2D LoadTexture(std::string file, bool alpha, std::string name);
    static Texture2D GetTexture(std::string name);

//    ResourceManager();

private:
    ResourceManager() { }
    static Texture2D loadTextureFromFile(std::string file, bool alpha);

};

