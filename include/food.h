#pragma once
#include "sprite_renderer.h"

class Food
{
public:
    Food();
    void draw(SpriteRenderer &renderer);
    void update(float dt);
    void addFood(const glm::vec2 &position);

private:
    glm::vec2 m_position {};
    float m_foodTimer {};
    bool m_isActive {};
};
