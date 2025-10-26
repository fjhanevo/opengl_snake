#include "game.h"
#include "config.h"
#include "constants.h"
#include "shader.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "text_renderer.h"

#include <GLFW/glfw3.h>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <sstream>
#include <format>

// helper function to get path for resources
static std::filesystem::path getPath(const std::string &relativePath)
{
    return std::filesystem::path(RESOURCE_DIR) / relativePath;
}

// ----- Random number generation -----
std::mt19937 dev;
std::random_device r;
std::uniform_int_distribution<> distX(1, Constants::SCREEN_WIDTH  / Constants::GRID_SIZE - 2);
std::uniform_int_distribution<> distY(1, Constants::SCREEN_HEIGHT / Constants::GRID_SIZE - 2);
std::uniform_int_distribution<> distBackground(0,12);    // For randomly generating background

// ----- Global variables ------
SpriteRenderer *Renderer{};
TextRenderer *Text{};

Game::Game(GLuint width, GLuint height, GLFWwindow *window)
    : m_width(width), m_height(height), m_score(0), m_moveTimer(0.0f),
    m_keys(), m_keysProcessed(), m_window(window), m_state(GAME_ACTIVE),
    m_snake(nullptr), m_food(nullptr), m_border(nullptr)
{}

Game::~Game()
{
    delete Renderer; 
    delete Text;
    delete m_snake;
    delete m_food;
    delete m_border;
    ResourceManager::clear();
}

void Game::init()
{
    // ----- Load shaders -----
    ResourceManager::loadShader(getPath("shaders/sprite.vert"), getPath("shaders/sprite.frag"), "sprite");
    // ----- Configure shaders -----
    glm::mat4 projection { glm::ortho(
        0.0f,
        static_cast<GLfloat>(m_width),
        static_cast<GLfloat>(m_height),
        0.0f,
        -1.0f,
        1.0f
    )};
    ResourceManager::getShader("sprite").use().setInt("sprite", 0);
    ResourceManager::getShader("sprite").use().setMat4("projection", projection);

    // ----- Load textures ----- 
    ResourceManager::loadTexture(getPath("textures/snake_head.png"), true, "snakeHead");
    ResourceManager::loadTexture(getPath("textures/snake_body.png"), true, "snakeBody");
    ResourceManager::loadTexture(getPath("textures/snake_tail.png"), true, "snakeTail");
    ResourceManager::loadTexture(getPath("textures/snake_corner.png"), true, "snakeCorner");
    ResourceManager::loadTexture(getPath("textures/apple.png"), true, "apple");
    ResourceManager::loadTexture(getPath("textures/fence.png"), true, "fence");
    // ----- Background textures ----- 
    ResourceManager::loadTexture(getPath("textures/background0.png"), true, "background0");
    ResourceManager::loadTexture(getPath("textures/background1.png"), true, "background1");
    ResourceManager::loadTexture(getPath("textures/background2.png"), true, "background2");
    ResourceManager::loadTexture(getPath("textures/background3.png"), true, "background3");
    ResourceManager::loadTexture(getPath("textures/background4.png"), true, "background4");
    ResourceManager::loadTexture(getPath("textures/background5.png"), true, "background5");
    ResourceManager::loadTexture(getPath("textures/background6.png"), true, "background6");
    ResourceManager::loadTexture(getPath("textures/background7.png"), true, "background7");
    ResourceManager::loadTexture(getPath("textures/background8.png"), true, "background8");
    ResourceManager::loadTexture(getPath("textures/background9.png"), true, "background9");
    ResourceManager::loadTexture(getPath("textures/background10.png"), true, "background10");
    ResourceManager::loadTexture(getPath("textures/background11.png"), true, "background11");
    ResourceManager::loadTexture(getPath("textures/background12.png"), true, "background12");

    Renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
    Text = new TextRenderer(m_width, m_height);
    Text->load(getPath("fonts/slkscr.ttf"), 24);
    
    m_snake = new Snake(m_width, m_height);
    m_food = new Food();
    m_border = new Border(m_width, m_height);
}   

void Game::update(float dt)
{
    constexpr GLfloat MOVE_INTERVAL { 0.15f };
    if (m_state == GAME_ACTIVE)
    {
        m_moveTimer += dt;

        // check if enough time has passed to move the snake
        if (m_moveTimer >= MOVE_INTERVAL)
        {
            Direction nextDir {m_snake->getNextDirection()};
            m_snake->setDirection(nextDir);
            m_snake->move();
            m_moveTimer = 0.0f;
        }

        m_food->update(dt);
        checkCollision();

        if (!m_food->getState())
        {
            addFood();
        }
    }

}

static std::vector<std::vector<int>> backgroundGrid{};

static void generateBackgroundGrid()
{
    // normalize
    const GLuint rows = Constants::SCREEN_WIDTH / Constants::GRID_SIZE;
    const GLuint cols = Constants::SCREEN_HEIGHT / Constants::GRID_SIZE;
    backgroundGrid.resize(rows, std::vector<int>(cols, 0));

    for (GLuint x{ 0 }; x < rows; ++x)
    {
        for (GLuint y{ 0 }; y < cols; ++y)
        {
            backgroundGrid[x][y] = distBackground(dev);
        }
    }
}

// Temporary function to draw background
static void fillBackground(SpriteRenderer &renderer)
{
    if (backgroundGrid.empty())
        generateBackgroundGrid();

    // normalize
    const GLuint rows = Constants::SCREEN_WIDTH / Constants::GRID_SIZE;
    const GLuint cols = Constants::SCREEN_HEIGHT / Constants::GRID_SIZE;
    for (GLuint x{ 0 }; x < rows; ++x)
    {
        for (GLuint y{ 0 }; y < cols; ++y)
        {
            renderer.drawSprite(
                ResourceManager::getTexture(std::format("background{}", backgroundGrid[x][y])),
                glm::vec2(x * Constants::GRID_SIZE, y * Constants::GRID_SIZE)
            );
        }
    }
}

void Game::render()
{
    std::stringstream ss; ss << m_score;
    if (m_state == GAME_ACTIVE) 
    {
        glClear(GL_COLOR_BUFFER_BIT);
        fillBackground(*Renderer);
        m_border->draw(*Renderer);
        m_snake->draw(*Renderer);

        if (m_food->getState())
            m_food->draw(*Renderer);

        Text->renderText("Score:"+ss.str(), Constants::GRID_SIZE, Constants::GRID_SIZE, 1.0f);
    }

    if (m_state == GAME_LOST)
    {
        Text->renderText(
            "Your Score:"+ss.str(), 
            floor(Constants::SCREEN_WIDTH / (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE,
            floor(Constants::SCREEN_HEIGHT/ (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE,
            1.0
        );
        
        Text->renderText(
            "Play Again [y/N]",
            floor(Constants::SCREEN_WIDTH / (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE,
            floor(Constants::SCREEN_HEIGHT / (2.0f * Constants::GRID_SIZE)) * Constants::GRID_SIZE + Constants::GRID_SIZE,
            1.0
        );
    }
}

void Game::processInput()
{
    if (m_state == GAME_ACTIVE) 
    {
        Direction newDir = m_snake->getNextDirection();
        if (m_keys[GLFW_KEY_W]) newDir = Direction::UP;
        if (m_keys[GLFW_KEY_A]) newDir = Direction::LEFT;
        if (m_keys[GLFW_KEY_S]) newDir = Direction::DOWN;
        if (m_keys[GLFW_KEY_D]) newDir = Direction::RIGHT;

        Direction currentDir = m_snake->getCurrentDirection();
        // prevent reversing the direction
        if (!((currentDir == Direction::UP   && newDir == Direction::DOWN)  ||
             (currentDir == Direction::DOWN  && newDir == Direction::UP)    ||
             (currentDir == Direction::LEFT  && newDir == Direction::RIGHT) ||
             (currentDir == Direction::RIGHT && newDir == Direction::LEFT)))
        {
            m_snake->queueDirection(newDir);
        } 
    }
    if (m_state == GAME_LOST)
    {
        if (m_keys[GLFW_KEY_Y] && !m_keysProcessed[GLFW_KEY_Y]) 
        {
            playAgain();
            m_keysProcessed[GLFW_KEY_Y] = true;
        }
        if (m_keys[GLFW_KEY_N] && !m_keysProcessed[GLFW_KEY_N]) 
        {
            glfwSetWindowShouldClose(m_window, true);
            m_keysProcessed[GLFW_KEY_N] = true;
        }
    }
}

void Game::checkCollision()
{
    // get the head position
    glm::vec2 snakeHead{ m_snake->getHeadPosition() };

    // check collision with food
    if (snakeHead == m_food->getPosition())
    {
        m_food->setState(false);
        m_snake->grow();
        m_score++;
    }

    // check collision with border
    if (snakeHead.x < Constants::GRID_SIZE || 
        snakeHead.x >= Constants::SCREEN_WIDTH - Constants::GRID_SIZE ||
        snakeHead.y < Constants::GRID_SIZE ||
        snakeHead.y >= Constants::SCREEN_HEIGHT - Constants::GRID_SIZE)
        m_state = GAME_LOST;

    // check collision with self
    // can't collide with itself if length is < 4
    if (m_snake->getLength() < 4)
        return;
    for (size_t i = 1; i < m_snake->getLength(); i++)
    {
        if (snakeHead == m_snake->getSegments()[i]) 
        {
            m_state = GAME_LOST;
            break;
        }
    }
}

void Game::addFood()
/* 
    Randomly generates a position for Food to be added.
    Makes sure the Food is not added on top of the Snake.
*/
{
    bool isValid { false }; 
    glm::vec2 pos{};
    while (!isValid)
    {
        pos.x = distX(r) * Constants::GRID_SIZE;
        pos.y = distY(r) * Constants::GRID_SIZE;

        // assume position is valid, check it doesn't spawn on snake
        isValid = true;

        for (const auto &segment : m_snake->getSegments())
        {
            if (segment == pos)
            {
                isValid = false;
                break;    
            }
        }
    }
    m_food->init(pos);
}

void Game::playAgain()
{
    m_score = 0;
    m_snake->init();
    m_food->setState(false);
    backgroundGrid.clear();
    m_state = GAME_ACTIVE;

}
