#pragma once

#include "sprite_renderer.h"
#include <glad/glad.h>
#include <vector>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake
{
public:
    Snake (GLuint width, GLuint height);

    void init();
    void draw(SpriteRenderer &renderer);
    void move();
    void grow();

    void setDirection(Direction dir);
    void queueDirection(Direction dir);

    // ----- get functions -----
    glm::vec2 getHeadPosition() const;
    Direction getCurrentDirection() const;
    Direction getNextDirection() const;
    int getLength() const;
    const std::vector<glm::vec2> &getSegments() const;

private:
    GLfloat applyHeadRotation();
    GLfloat applyBodyRotation();
    bool isCorner(const size_t &i);
    std::vector<glm::vec2> m_segments{};
    GLuint m_width, m_height;
    Direction m_currentDirection {};
    Direction m_nextDirection {};
};
