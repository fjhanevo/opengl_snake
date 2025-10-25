#include "shader.h"
#include <glm/fwd.hpp>
#include <string>
#include <iostream>

Shader &Shader::use()
{
    glUseProgram(m_ID);
    return *this;
}

void Shader::compile(std::string_view vertexSource, std::string_view fragmentSource)
{
    GLuint sVertex, sFragment;

    // ------ Vertex shader ------ 
    // get pointer and length from string_view
    const char *vertexSourcePtr {vertexSource.data()};   // get pointer and length from string_view
    const GLint vertexSourceLen {static_cast<GLint>(vertexSource.length())};
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSourcePtr, &vertexSourceLen);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    // ------ Fragment shader ------ 
    // get pointer and length from string_view
    const char *fragmentSourcePtr {fragmentSource.data()};
    const GLint fragmentSourceLen {static_cast<GLint>(fragmentSource.length())};
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSourcePtr, &fragmentSourceLen);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    m_ID = glCreateProgram();
    glAttachShader(m_ID, sVertex);
    glAttachShader(m_ID, sFragment);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");

    // delete when linking is done
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

void Shader::setInt(const std::string &name, GLint value, bool useShader)
{
    if (useShader)
        use();
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, GLfloat value, bool useShader)
{
    if (useShader)
        use();

}

void Shader::setVec2(const std::string &name, glm::vec2 &vec, bool useShader)
{
    if (useShader)
        use();
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), vec.x, vec.y);
}


void Shader::setVec3(const std::string &name, glm::vec3 &vec, bool useShader)
{
    if (useShader)
        use();
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), vec.x, vec.y, vec.z);
}


void Shader::setVec4(const std::string &name, glm::vec4 &vec, bool useShader)
{
    if (useShader)
        use();
    glUniform4f(glGetUniformLocation(m_ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMat2(const std::string &name, glm::mat2 &mat, bool useShader)
{
    if (useShader)
        use();
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, glm::mat3 &mat, bool useShader)
{
    if (useShader)
        use();
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void Shader::setMat4(const std::string &name, glm::mat4 &mat, bool useShader)
{
    if (useShader)
        use();
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, const std::string &type)
{
    GLint success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << '\n'
                << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << '\n'
                << infoLog << std::endl;
        }
    }
}
