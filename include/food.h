#pragma once
#include "sprite_renderer.h"

class Food
{
public:
    Food();
    void draw(SpriteRenderer &renderer);
    void update(float dt);
    void init(const glm::vec2 &position);
    bool getState() const;
    const glm::vec2 getPosition() const;
    void setState(bool state);

private:
    glm::vec2 m_position {};
    float m_foodTimer {};
    bool m_isActive {};
};
