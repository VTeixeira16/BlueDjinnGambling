#include "BD_ResourceManager.hpp"
#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>

//static std::map<std::string, Texture2D> Textures;
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader>    ResourceManager::Shaders;
std::map<std::string, Font2D>    ResourceManager::Fonts;

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(std::string file, bool alpha, std::string name){
    //TODO - Caso nome já exista, retornará um erro
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name){
    //TODO - Criar situacao de erro
    return Textures[name];
}

Font2D ResourceManager::LoadFont(std::string file, unsigned int size, std::string name){
    Fonts[name] = loadFontFromFile(file, size);
    return Fonts[name];

}

Font2D ResourceManager::GetFont(std::string name){
    return Fonts[name];
}



Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

//Avaliar possibilidade de mudar para estatico
Texture2D ResourceManager::loadTextureFromFile(std::string file, bool alpha){
//Texture2D ResourceManager::loadTextureFromFile(){

    // create texture object
    Texture2D texture;


    //TODO - definição de alpha vai vir da identificação do formato de arquivo
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }

    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
//    unsigned char* data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);

    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);

    return texture;
}

Font2D ResourceManager::loadFontFromFile(std::string file, unsigned int size){
    Font2D font;

//    std::cout << "file:[" << file << "] Size:[" << size << "]." << std::endl;

//    std::cout << "ID:[" << font.ID << "] Size:[" << font.size << "]." << std::endl;

    font.Generate(file, size);

    return font;
}
