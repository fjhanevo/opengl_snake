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

    // Set Direction DOWN again, this is mainly for the playAgain function
    m_currentDirection = Direction::DOWN; 
    m_nextDirection = Direction::DOWN;
}

void Snake::draw(SpriteRenderer &renderer)
{
    // Draw the head first
    renderer.drawSprite(
            ResourceManager::getTexture("snakeHead"),
            m_segments[0],
            applyHeadRotation()
        );

    // Draw the body
    for (size_t i{ 1 }; i < m_segments.size() - 1; i++)
    {
        renderer.drawSprite(
            (isCorner(i)) ? ResourceManager::getTexture("snakeCorner") : ResourceManager::getTexture("snakeBody"),
            m_segments[i],
            (isCorner(i)) ? applyCornerRotation(i) : applyBodyRotation(i)
        );
    }

    // Draw the tail
    if (m_segments.size() > 1)
    {
        renderer.drawSprite(
            ResourceManager::getTexture("snakeTail"),
            m_segments.back(),
            applyBodyRotation(m_segments.size()-1) + 180.0f
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

// Helper function to get rotation
static GLfloat getRotation(const glm::vec2 &prevSegment, const glm::vec2 &currSegment)
{
    // check if they're on the same horizontal line
    if (prevSegment.y == currSegment.y)
    {
        if (prevSegment.x < currSegment.x) return 270.f;    // moves to the RIGHT
        else return 90.0f;                                  // moves to the LEFT
    }

    // check if the're on the same vertical line
    else if (prevSegment.x == currSegment.x)
    {
        if (prevSegment.y < currSegment.y) return 0.0f;     // moves DOWN
        else return 180.0f;                                 // moves UP
    }

    // default return value
    return 0.0f;
}

GLfloat Snake::applyHeadRotation()
{
    switch (getCurrentDirection())
    {
        case Direction::UP:     return 180.0f; break;
        case Direction::DOWN:   return 0.0f; break;
        case Direction::LEFT:   return 90.0f; break;
        case Direction::RIGHT:  return 270.0f; break;
        default:                return 0.0f;
    }
}

GLfloat Snake::applyBodyRotation(const size_t &i)
{
    return getRotation(m_segments[i-1], m_segments[i]);
}

GLfloat Snake::applyCornerRotation(const size_t &i)
{
    glm::vec2 prev{ m_segments[i-1] };
    glm::vec2 curr{ m_segments[i] };
    glm::vec2 next{ m_segments[i+1] };

    // Find the relative positions of the neighbors
    bool prevUp     = prev.y < curr.y;
    bool prevDown   = prev.y > curr.y;
    bool prevLeft   = prev.x < curr.x;
    bool prevRight  = prev.x > curr.x;

    bool nextUp     = next.y < curr.y;
    bool nextDown   = next.y > curr.y;
    bool nextLeft   = next.x < curr.x;
    bool nextRight  = next.x > curr.x;

    // DOWN and RIGHT
    if ((prevDown && nextRight) || (prevRight && nextDown))
        return 90.0f;
    // DOWN and LEFT 
    if ((prevDown && nextLeft) || (prevLeft && nextDown))
        return 180.0f;

    // UP and LEFT
    if ((prevUp && nextLeft) || (prevLeft && nextUp))
        return 270.0f;
    
    // UP and RIGHT 
    if ((prevUp && nextRight) || (prevRight && nextUp))
        return 0.0f;
    
    // default return value
    return 0.0f;
}

bool Snake::isCorner(const size_t &i)
{
    // Check segment[i] position against it's neighbors
    glm::vec2 prevSegment{ m_segments[i-1] };
    glm::vec2 nextSegment{ m_segments[i+1] };

    // If the neighboring positions are on the same axis they are not corners
    if (m_segments[i].x == prevSegment.x && m_segments[i].x == nextSegment.x || 
        m_segments[i].y == prevSegment.y && m_segments[i].y == nextSegment.y)
        return false;

    return true;
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


