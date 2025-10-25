#pragma once
#include "sprite_renderer.h"

class Food
{
public:
    Food();
    void draw(SpriteRenderer &renderer);
    void update(float dt);
    void spawn(const glm::vec2 &position);

private:
    float foodTimer {};
    bool isActive {};
};
