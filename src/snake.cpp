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

    glm::vec2 headPos = glm::vec2(
        floor(m_width / (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE,
        floor(m_height / (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE
    );
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
            m_segments[0]
            //TODO: Add head rotation
        );

    // Draw the body
    for (size_t i = 1; i < m_segments.size() - 1; i++)
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
