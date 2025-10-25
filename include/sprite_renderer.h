#pragma once

#include "shader.h"
#include "texture.h"

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
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotation = 0.0f,
        glm::vec3 color = glm::vec3(1.0f)
    );

private:
    Shader m_shader {};
    GLuint m_quadVAO {};

    void initRenderData();
};
