#pragma once

#include "sprite_renderer.h"
#include <glad/glad.h>
#include <vector>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake
{
public:
    Snake (GLuint width, GLuint height);

    void draw(SpriteRenderer &renderer);
    void move();
    void grow();
    void resetSnake(GLuint width, GLuint height);

    void setDirection(Direction dir);
    void queueDirection(Direction dir);

    // ----- get functions -----
    glm::vec2 getHeadPosition() const;
    Direction getCurrentDirection() const;
    Direction getNextDirection() const;
    int getLength() const;
    const std::vector<glm::vec2> &getSegments() const;

private:
    std::vector<glm::vec2> m_segments{};
    Direction m_currentDirection {};
    Direction m_nextDirection {};
};
