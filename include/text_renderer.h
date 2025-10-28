#pragma once

#include "texture.h"
#include "shader.h"
#include <map>

struct Character
{
    GLuint TextureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    long advance;
};

class TextRenderer
{
public:
    // store precompiled characters
    std::map<char, Character> m_characters;
    Shader m_textShader;
    TextRenderer(GLuint width, GLuint height);

    // precompiles a list of characters 
    void load(const std::string &font, GLuint fontSize);
    // renders a string of text using the precompiled list of characters
    void renderText(
        const std::string &text, 
        GLfloat x, 
        GLfloat y, 
        GLfloat scale = 1.0f,
        glm::vec3 color = glm::vec3(1.0f)
    );

    glm::vec2 getTextSize(const std::string &text, GLfloat scale = 1.0f);

private:
    GLuint m_VAO{}, m_VBO{};
};
