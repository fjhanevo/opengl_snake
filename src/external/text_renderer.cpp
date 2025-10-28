#include "text_renderer.h"
#include "resource_manager.h"
#include "config.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H


std::string vertPath{ std::string(RESOURCE_DIR) + "shaders/text.vert" };
std::string fragPath{ std::string(RESOURCE_DIR) + "shaders/text.frag" };

TextRenderer::TextRenderer(GLuint width, GLuint height)
{
    // load and configure shaders
    m_textShader = ResourceManager::loadShader(vertPath, fragPath, "text");
    glm::mat4 projection{
        glm::ortho(
            0.0f,
            static_cast<GLfloat>(width), 
            static_cast<GLfloat>(height), 
            0.0f
        )
    };

    m_textShader.setMat4("projection", projection, true);
    m_textShader.setInt("text", 0);

    // configure VAO/VBO for texture quads
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::load(const std::string &font, GLuint fontSize)
{
    // clear previously loaded characters
    m_characters.clear();
    FT_Library ft{};
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // load font as face
    FT_Face face{};

    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // set the size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // pre-load and compile the first 128 ASCII characters
    for (GLubyte c{ 0 }; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // generate texture
        GLuint texture{};
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Store Characters for later use
        Character character{
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x

        };
        m_characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // destroy when finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::renderText(
    const std::string &text, 
    GLfloat x, 
    GLfloat y,
    GLfloat scale, 
    glm::vec3 color)
{
    m_textShader.use();
    m_textShader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    // iterate through all characters
    std::string::const_iterator c{};
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch{ m_characters[*c] };

        GLfloat xPos{ x + ch.bearing.x * scale };
        GLfloat yPos{ y + (m_characters['H'].bearing.y - ch.bearing.y) * scale };

        GLfloat w{ ch.size.x * scale };
        GLfloat h{ ch.size.y * scale };

        // update VBO for each character
        GLfloat vertices[6][4]{
            { xPos,     yPos + h, 0.0f, 1.0f },
            { xPos + w, yPos,     1.0f, 0.0f },
            { xPos,     yPos,     0.0f, 0.0f },

            { xPos,     yPos + h, 0.0f, 1.0f },
            { xPos + w, yPos + h, 1.0f, 1.0f },
            { xPos + w, yPos,     1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // advance cursors for next glyph
        x += (ch.advance >> 6) * scale; // bitshift by 6
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Get the size of rendered text
glm::vec2 TextRenderer::getTextSize(const std::string &text, GLfloat scale)
{
    GLfloat totalWidth{}, maxHeight{};
    // iterate through the characters  
    std::string::const_iterator c{};

    for (c = text.begin(); c != text.end(); c++)
    {
        // Get width and height of current character and add to the total
        Character ch{ m_characters[*c] };

        totalWidth += (ch.advance >> 6) * scale;

        GLfloat charHeight { ch.size.y  * scale };
        if (charHeight > maxHeight)
            maxHeight = charHeight;
    }
    return glm::vec2(totalWidth, maxHeight);
}
