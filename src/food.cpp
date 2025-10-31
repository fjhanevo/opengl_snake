#include "food.h"
#include "constants.h"
#include "resource_manager.h"

constexpr float FOOD_TIME = 10.0f;
Food::Food()
    : m_position(0.0f, 0.0f), m_foodTimer(FOOD_TIME), m_isActive(false)
{}

void Food::draw(SpriteRenderer &renderer)
{
    renderer.drawSprite(
        ResourceManager::getTexture("apple"),
        m_position
        );
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

void Food::init(const glm::vec2& position)
{
    m_isActive = true; 
    m_foodTimer = FOOD_TIME;
    m_position = position;
}

bool Food::getState() const
{
    return m_isActive;
}
const glm::vec2 Food::getPosition() const
{
    return glm::vec2(
        m_position.x / Constants::GRID_SIZE,
        m_position.y / Constants::GRID_SIZE
    );
}

void Food::setState(bool state)
{
    m_isActive = state;
}
