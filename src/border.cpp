#include "border.h"
#include "constants.h"
#include "resource_manager.h"

Border::Border()
{
    // clear the vector  
    m_openGrids.clear();

    // Check if rows (width) is even or odd
    if (Constants::ROWS % 2 == 0)
    {
        // add two open positions since it's even
        GLint xCenter1 { (Constants::ROWS / 2) - 1 };
        GLint xCenter2 { Constants::ROWS / 2 };

        m_openGrids.emplace_back(xCenter1, 0);                      // Open Top position 1
        m_openGrids.emplace_back(xCenter2, 0);                      // Open Top position 2
        m_openGrids.emplace_back(xCenter1, Constants::COLS - 1);    // Open Bottom position 1
        m_openGrids.emplace_back(xCenter2, Constants::COLS - 1);    // Open Bottom position 2
    }

    else 
    {
        GLint xCenter { Constants::ROWS / 2 };
        m_openGrids.emplace_back(xCenter, 0);                       // Open Top position
        m_openGrids.emplace_back(xCenter, Constants::COLS - 1);     // Open Bottom position
    }

    // check if columns (height) is even or odd
    if (Constants::COLS % 2 == 0)
    {
        GLint yCenter1 { (Constants::COLS / 2) - 1 };
        GLint yCenter2 { (Constants::COLS / 2) };

        m_openGrids.emplace_back(0, yCenter1);                      // Open Left position 1
        m_openGrids.emplace_back(0, yCenter2);                      // Open Left position 2
        m_openGrids.emplace_back(Constants::ROWS - 1, yCenter1);    // Open Left position 1
        m_openGrids.emplace_back(Constants::ROWS - 1, yCenter2);    // Open Left position 2
    }

    else 
    {
        GLint yCenter {Constants::COLS / 2};

        m_openGrids.emplace_back(0, yCenter);                       // Open Left position
        m_openGrids.emplace_back(Constants::ROWS - 1, yCenter);     // Open Left position
    }
}

void Border::draw(SpriteRenderer &renderer)
{
    for (GLuint x{ 1 }; x < Constants::ROWS - 1; ++x) 
    {
        // Draw top border
        renderer.drawSprite(
            (isOpen({x, 0})) ? ResourceManager::getTexture("hole") : ResourceManager::getTexture("fence"),
            glm::vec2(x * Constants::GRID_SIZE, 0.0f)
        );

        // Draw bottom border
        renderer.drawSprite(
            (isOpen({x, Constants::COLS - 1})) ? ResourceManager::getTexture("hole") : ResourceManager::getTexture("fence"),
            glm::vec2(x * Constants::GRID_SIZE, (Constants::COLS - 1) * Constants::GRID_SIZE),
            180.0f
        );

    }

    for (GLuint y{ 1 }; y < Constants::COLS - 1; ++y)
    {
        // Left border column
        renderer.drawSprite(
            (isOpen({0,y})) ? ResourceManager::getTexture("hole") : ResourceManager::getTexture("fence"),
            glm::vec2(0, y * Constants::GRID_SIZE),
            270.0f
        );

        // Right border column
        renderer.drawSprite(
            (isOpen({(Constants::ROWS - 1), y})) ? ResourceManager::getTexture("hole") : ResourceManager::getTexture("fence"),
            glm::vec2((Constants::ROWS -1)* Constants::GRID_SIZE, y * Constants::GRID_SIZE),
            90.0f 
        );
    }
}

bool Border::isOpen(const glm::vec2& gridPos) const
{
    for (const auto& openPos : m_openGrids)
    {
        if (openPos == gridPos)
            return true;
    }
    return false;
}

std::vector<glm::vec2> Border::getOpenGrids() const
{
    return m_openGrids;
}
