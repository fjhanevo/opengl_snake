#pragma once
#include "sprite_renderer.h"

class Border
{
public:
    Border(GLuint width, GLuint height);
    void draw(SpriteRenderer &renderer);
private:
    GLuint m_width{}, m_height{};
};
