#include "border.h"
#include "constants.h"
#include "resource_manager.h"

Border::Border(GLuint width, GLuint height)
    : m_width(width), m_height(height)
{}

void Border::draw(SpriteRenderer &renderer)
{
    for (GLuint x{ 1 }; x < Constants::ROWS - 1; ++x) 
    {
        // Draw top border
        renderer.drawSprite(
            (x == 9 || x == 10) ? ResourceManager::getTexture("background0") : ResourceManager::getTexture("fence"),
            glm::vec2(x * Constants::GRID_SIZE, 0.0f)
        );

        // Draw bottom border
        renderer.drawSprite(
            (x == 9 || x == 10) ? ResourceManager::getTexture("background0") : ResourceManager::getTexture("fence"),
            glm::vec2(x * Constants::GRID_SIZE, m_height - Constants::GRID_SIZE),
            180.0f
        );

    }

    for (GLuint y{ 1 }; y < Constants::COLS - 1; ++y)
    {
        // Left border column
        renderer.drawSprite(
            (y == 7) ? ResourceManager::getTexture("background0") : ResourceManager::getTexture("fence"),
            glm::vec2(0, y * Constants::GRID_SIZE),
            270.0f
        );

        // Right border column
        renderer.drawSprite(
            ResourceManager::getTexture("fence"),
            glm::vec2(m_width - Constants::GRID_SIZE, y * Constants::GRID_SIZE),
            90.0f 
        );
    }
}
