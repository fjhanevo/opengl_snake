#include "food.h"
#include "resource_manager.h"

constexpr float FOOD_TIME = 10.0f;
Food::Food()
    : m_position(0.0f, 0.0f), m_foodTimer(FOOD_TIME), m_isActive(false)
{}

void Food::draw(SpriteRenderer &renderer)
{
    // only draw if there is a food object
    if (m_isActive)
    {
        renderer.drawSprite(
            ResourceManager::getTexture("apple"),
            m_position
            );
    }
}

void Food::update(float dt)
{
    if (m_isActive)
    {
        m_foodTimer -= dt;

        // remove food if the timer runs out
        if (m_foodTimer <= 0.0f)
        {
            m_isActive = false;
        }
    }
}

void Food::addFood(const glm::vec2& position)
{
    m_isActive = true; 
    m_foodTimer = FOOD_TIME;
    m_position = position;
}
