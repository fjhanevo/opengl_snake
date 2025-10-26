#include "border.h"
#include "constants.h"
#include "resource_manager.h"

Border::Border(GLuint width, GLuint height)
    : m_width(width), m_height(height)
{}

void Border::draw(SpriteRenderer &renderer)
{
    for (GLuint x{ Constants::GRID_SIZE }; x < m_width - Constants::GRID_SIZE; x += Constants::GRID_SIZE) 
    {
        // Draw top border
        renderer.drawSprite(
            ResourceManager::getTexture("fence"),
            glm::vec2(x, 0.0f)
        );
        // Draw bottom border
        renderer.drawSprite(
            ResourceManager::getTexture("fence"),
            glm::vec2(x, m_height - Constants::GRID_SIZE),
            180.0f
        );

    }

    for (GLuint y{ Constants::GRID_SIZE }; y < m_height - Constants::GRID_SIZE; y += Constants::GRID_SIZE)
    {
        // Left border column
        renderer.drawSprite(
            ResourceManager::getTexture("fence"),
            glm::vec2(0, y),
            270.0f
        );

        // Right border column
        renderer.drawSprite(
            ResourceManager::getTexture("fence"),
            glm::vec2(m_width - Constants::GRID_SIZE, y),
            90.0f 
        );
    }
}
