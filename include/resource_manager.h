#pragma once

#include <map>
#include <filesystem>
#include "shader.h"
#include "texture.h"

class ResourceManager
/* 
Static class for resource management
Stores all shaders and textures
*/
{
public:
    // resource storage
    static std::map<std::string, Shader>    shaders;
    static std::map<std::string, Texture2D> textures; 

    // loads and generates a shader program from vertex and fragment files
    static Shader loadShader(
        const std::filesystem::path &vShaderFile, 
        const std::filesystem::path &fShaderFile,
        const std::string &name
    );

    static Shader &getShader(const std::string &name);

    // loads and generate textures 
    static Texture2D loadTexture(
        const std::filesystem::path &file, 
        bool alpha, 
        const std::string &name
    );

    static Texture2D &getTexture(const std::string &name);

    // cleanup function
    static void clear();

private:
    // private constructor
    ResourceManager() {}

    static Shader loadShaderFromFile(
        const std::filesystem::path &vShaderFile,
        const std::filesystem::path &fShaderFile
    );

    static Texture2D loadTextureFromFile(
        const std::filesystem::path &file,
        bool alpha
    );
};
