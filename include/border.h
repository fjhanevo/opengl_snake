#pragma once
#include "sprite_renderer.h"
#include <vector>

class Border
{
public:
    Border(GLuint width, GLuint height);
    void draw(SpriteRenderer &renderer);
    std::vector<glm::vec2> m_openGrids{};
private:
    GLuint m_width{}, m_height{};
};
