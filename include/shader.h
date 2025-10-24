#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>

class Shader
{
public:
    // program ID
    unsigned int ID;

    // constructor
    Shader() { }

    // sets current shader as active
    Shader &use();
    
    // compile shaders from source
    void compile(std::string_view vertexSource, std::string_view fragmentSource);

    // utility uniform functions
    void set_int(std::string_view name, int value, bool useShader = false);
    void set_float(std::string_view name, float value, bool useShader = false);

    void set_vec2(std::string_view name, glm::vec2 &vec, bool useShader = false);
    void set_vec3(std::string_view name, glm::vec3 &vec, bool useShader = false);
    void set_vec4(std::string_view name, glm::vec4 &vec, bool useShader = false);

    void set_mat2(std::string_view name, glm::mat2 &mat, bool useShader = false);
    void set_mat3(std::string_view name, glm::mat3 &mat, bool useShader = false);
    void set_mat4(std::string_view name, glm::mat4 &mat, bool useShader = false);
private:
    void check_compile_errors(unsigned int shader, std::string type);

};

