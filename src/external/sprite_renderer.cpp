#include "sprite_renderer.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    m_shader = shader;
    initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &m_quadVAO);
}
void SpriteRenderer::drawSprite(
    Texture2D &texture,
    glm::vec2 position,
    GLfloat rotation,
    glm::vec2 size,
    glm::vec3 color)
{
    m_shader.use();
    glm::mat4 model = glm::mat4(1.0f);

    // ---- Transformation -----
    model = glm::translate(model, glm::vec3(position, 0.0f));

    // steps: translate->rotation->translate->scale
    // move origin of the rotation to the center of quad
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    // rotate the model
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    // move the origin back
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_shader.setMat4("model", model);

    // render textured quads
    m_shader.setVec3("spriteColor", color);
    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    // draw triangles
    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    GLuint VBO{};
    GLfloat vertices[] = {
        // position     // texture
        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f,
        0.0f, 0.0f,     0.0f, 0.0f,

        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
