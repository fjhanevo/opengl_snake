#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>
#include <string>

class Shader
{
public:
    // program ID
    GLuint m_ID {};

    // constructor
    Shader() { }

    // sets current shader as active
    Shader &use();
    
    // compile shaders from source
    void compile(std::string_view vertexSource, std::string_view fragmentSource);

    // utility uniform functions
    void setInt(const std::string &name, int value, bool useShader = false);
    void setFloat(const std::string &name, float value, bool useShader = false);

    void setVec2(const std::string &name, glm::vec2 &vec, bool useShader = false);
    void setVec3(const std::string &name, glm::vec3 &vec, bool useShader = false);
    void setVec4(const std::string &name, glm::vec4 &vec, bool useShader = false);

    void setMat2(const std::string &name, glm::mat2 &mat, bool useShader = false);
    void setMat3(const std::string &name, glm::mat3 &mat, bool useShader = false);
    void setMat4(const std::string &name, glm::mat4 &mat, bool useShader = false);

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

