#include "snake.h"
#include "constants.h"
#include "resource_manager.h"

Snake::Snake(GLuint width, GLuint height)
    : m_width(width), m_height(height),
    m_currentDirection(Direction::DOWN), m_nextDirection(Direction::DOWN)
{
    init();
}

void Snake::init()
{
    // clear snake body 
    m_segments.clear();

    glm::vec2 headPos{ glm::vec2(
        floor(m_width / (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE,
        floor(m_height / (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE
    )};
    m_segments.push_back(headPos);

    // Add two more body parts
    m_segments.push_back(glm::vec2(headPos.x, headPos.y - Constants::GRID_SIZE));
    m_segments.push_back(glm::vec2(headPos.x, headPos.y - 2 * Constants::GRID_SIZE));
}

void Snake::draw(SpriteRenderer &renderer)
{
    // Draw snake head first
    renderer.drawSprite(
            ResourceManager::getTexture("snakeHead"),
            m_segments[0],
            applyHeadRotation()
        );

    // Draw the body
    for (size_t i{ 1 }; i < m_segments.size() - 1; i++)
    {
        renderer.drawSprite(
            ResourceManager::getTexture("snakeBody"),   //TODO: Change body texture based on corners
            m_segments[i]
            //TODO:: Add rotation (account for corners)
        );
    }

    if (m_segments.size() > 1)
    {
        renderer.drawSprite(
            ResourceManager::getTexture("snakeTail"),
            m_segments[m_segments.size()-1]
            //TODO:: Add rotation
        );
    }
}

void Snake::move()
{
    // shift body backwards
    for (size_t i{ m_segments.size() - 1 }; i > 0; i--)
    {
        m_segments[i] = m_segments[i-1];
    }

    // update head position
    switch(m_currentDirection)
    {
        case Direction::UP:     m_segments[0].y -= Constants::GRID_SIZE; break;
        case Direction::DOWN:   m_segments[0].y += Constants::GRID_SIZE; break;
        case Direction::LEFT:   m_segments[0].x -= Constants::GRID_SIZE; break;
        case Direction::RIGHT:  m_segments[0].x += Constants::GRID_SIZE; break;
    }
}

void Snake::grow()
{
    m_segments.push_back(m_segments.back());
}

void Snake::setDirection(Direction dir)
{
    m_currentDirection = dir;
}

void Snake::queueDirection(Direction dir)
{
    m_nextDirection = dir;
}

Direction Snake::getCurrentDirection() const
{
    return m_currentDirection;
}

Direction Snake::getNextDirection() const
{
    return m_nextDirection;
}

glm::vec2 Snake::getHeadPosition() const
{
    return m_segments[0];
}

int Snake::getLength() const
{
    return m_segments.size();
}

const std::vector<glm::vec2> &Snake::getSegments() const
{
    return m_segments;
}

GLfloat Snake::applyHeadRotation()
{
    switch (getCurrentDirection())
    {
        case Direction::UP:     return 180.0f; break;
        case Direction::DOWN:   return 0.0f; break;
        case Direction::LEFT:   return 90.0f; break;
        case Direction::RIGHT:  return -90.0f; break;
        default:                return 0.0f;
    }
}
