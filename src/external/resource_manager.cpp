#include "resource_manager.h"
#include "shader.h"
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::map<std::string, Shader>    ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader ResourceManager::loadShader(
    const std::filesystem::path &vShaderFile, 
    const std::filesystem::path &fShaderFile, 
    const std::string &name)
{
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
    return shaders[name];
}

Shader &ResourceManager::getShader(const std::string &name)
{
    return shaders.at(name);
}

Texture2D ResourceManager::loadTexture(
    const std::filesystem::path &file,
    bool alpha,
    const std::string &name)
{
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture2D &ResourceManager::getTexture(const std::string &name)
{
    return textures.at(name);
}

void ResourceManager::clear()
{
    for (auto it : shaders)
        glDeleteProgram(it.second.m_ID);
    for (auto it : textures)
        glDeleteTextures(1, &it.second.m_ID);
}

Shader ResourceManager::loadShaderFromFile(
    const std::filesystem::path &vShaderFile,
    const std::filesystem::path &fShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;

    try 
    {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream{}, fShaderStream{};

        // read file buffer into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // close when done reading
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // convert stream to string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    Shader shader {};
    shader.compile(vertexCode, fragmentCode);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const std::filesystem::path &file, bool alpha)
{
    Texture2D texture {};
    if (alpha)
    {
        texture.m_internalFormat = GL_RGBA;
        texture.m_imageFormat = GL_RGBA;
    }

    // load image
    int width{}, height{}, nrChannels{};
    unsigned char *data = stbi_load(file.string().c_str(), &width, &height, &nrChannels, 0);
    texture.generate(width, height, data);

    // free image data
    stbi_image_free(data);
    return texture;
}
