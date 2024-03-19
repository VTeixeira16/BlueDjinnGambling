#include "BD_ResourceManager.hpp"
#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>

//static std::map<std::string, Texture2D> Textures;
std::map<std::string, Texture2D> ResourceManager::Textures;

Texture2D ResourceManager::LoadTexture(std::string file, bool alpha, std::string name){
    //TODO - Caso nome já exista, retornará um erro
    std::cout << "file:" << file << std::endl;
    std::cout << "alpha:" << alpha << std::endl;
    std::cout << "file:" << name << std::endl;

    Textures[name] = loadTextureFromFile(file, alpha);
//    loadTextureFromFile();


    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    //TODO - Criar situacao de erro
    return Textures[name];
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

