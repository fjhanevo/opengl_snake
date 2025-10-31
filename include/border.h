#pragma once
#include "sprite_renderer.h"
#include <vector>

class Border
{
public:
    Border();
    void draw(SpriteRenderer &renderer);
    bool isOpen(const glm::vec2 &gridPos) const;
    std::vector<glm::vec2> getOpenGrids() const;
private:
    GLuint m_width{}, m_height{};
    std::vector<glm::vec2> m_openGrids{};
};
