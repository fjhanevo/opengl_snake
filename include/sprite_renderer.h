#pragma once

#include "shader.h"
#include "texture.h"
#include "constants.h"

class SpriteRenderer
{
public:
    // constructor and destructor
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    // drawing function
    void drawSprite(
        Texture2D &texture,
        glm::vec2 position,
        glm::vec2 size = glm::vec2(Constants::GRID_SIZE, Constants::GRID_SIZE),
        GLfloat rotation = 0.0f,
        glm::vec3 color = glm::vec3(1.0f)
    );

private:
    Shader m_shader {};
    GLuint m_quadVAO {};

    void initRenderData();
};
