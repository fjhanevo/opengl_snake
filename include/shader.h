#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>

class Shader
{
public:
    // program ID
    unsigned int m_ID;

    // constructor
    Shader() { }

    // sets current shader as active
    Shader &use();
    
    // compile shaders from source
    void compile(std::string_view vertexSource, std::string_view fragmentSource);

    // utility uniform functions
    void setInt(std::string_view name, int value, bool useShader = false);
    void setFloat(std::string_view name, float value, bool useShader = false);

    void setVec2(std::string_view name, glm::vec2 &vec, bool useShader = false);
    void setVec3(std::string_view name, glm::vec3 &vec, bool useShader = false);
    void setVec4(std::string_view name, glm::vec4 &vec, bool useShader = false);

    void setMat2(std::string_view name, glm::mat2 &mat, bool useShader = false);
    void setMat3(std::string_view name, glm::mat3 &mat, bool useShader = false);
    void setMat4(std::string_view name, glm::mat4 &mat, bool useShader = false);
private:
    void checkCompileErrors(unsigned int shader, std::string type);

};

