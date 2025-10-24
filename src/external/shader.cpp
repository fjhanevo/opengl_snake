#include "shader.h"
#include <string>

Shader &Shader::use()
{
    glUseProgram(m_ID);
    return *this;
}

void Shader::compile(std::string_view vertexSource, std::string_view fragmentSource)
{
    unsigned int sVertex, sFragment;

    // ------ Vertex shader ------ 
    // get pointer and length from string_view
    const char *vertexSourcePtr {vertexSource.data()};   // get pointer and length from string_view
    const int vertexSourceLen {(int)vertexSource.length()};
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSourcePtr, &vertexSourceLen);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    // ------ Fragment shader ------ 
    // get pointer and length from string_view
    const char *fragmentSourcePtr {fragmentSource.data()};
    const int fragmentSourceLen {(int)fragmentSource.length()};
    sFragment = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sFragment, 1, &fragmentSourcePtr, &fragmentSourceLen);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    m_ID = glCreateProgram();
    glAttachShader(m_ID, sVertex);
    glAttachShader(m_ID, sFragment);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");


}
