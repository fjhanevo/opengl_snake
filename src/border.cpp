#include "border.h"
#include "constants.h"
#include "resource_manager.h"

Border::Border(GLuint width, GLuint height)
    : m_width(width), m_height(height)
{
    // Top and bottom positions
    for (GLuint x {1}; x < Constants::ROWS - 1; ++x)
    {
        GLfloat xCenter { x * Constants::GRID_SIZE + Constants::GRID_SIZE / 2.0f };
        if (x % 2 == 0) // add 2 openings if even 
        {
            m_openGrids.emplace_back(xCenter - Constants::GRID_SIZE / 4.0f, Constants::GRID_SIZE / 2.0f);
            m_openGrids.emplace_back(xCenter - Constants::GRID_SIZE / 4.0f, m_height - Constants::GRID_SIZE / 2.0f);
        }
        else 
        {
            m_openGrids.emplace_back(xCenter, Constants::GRID_SIZE / 2.0f);
        }
    }

    for (GLuint y {1}; y < Constants::COLS- 1; ++y)
    {
        GLfloat yCenter { y * Constants::GRID_SIZE + Constants::GRID_SIZE / 2.0f };
        if (y % 2 == 0) // add 2 openings if even 
        {
            m_openGrids.emplace_back(Constants::GRID_SIZE / 2.0f, yCenter - Constants::GRID_SIZE / 4.0f);
            m_openGrids.emplace_back(m_width - Constants::GRID_SIZE / 2.0f, yCenter + Constants::GRID_SIZE);
        }
        else 
        {
            m_openGrids.emplace_back(Constants::GRID_SIZE / 2.0f, yCenter);
        }
    }

}

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
