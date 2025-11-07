#pragma once

#include "shader.h"
#include "snake.h"
#include "food.h"
#include "border.h"
#include <GLFW/glfw3.h>
#include <memory>


enum GameState
{
    GAME_ACTIVE,
    GAME_LOST
};

class Game
{
public:
    // constructor and desctructor
    Game(GLuint width, GLuint height, GLFWwindow *window);
    ~Game();

    // ---- Game functions -----
    void init();
    void update(float dt);
    void render();
    void processInput();
    void playAgain();

    // ----- Public member variables -----
    GLuint m_width{};
    GLuint m_height{};
    bool m_keys[1024];
    bool m_keysProcessed[1024];

private:
    // ----- Private member variables -----
    GLuint m_score{};
    GLfloat m_moveTimer {};

    GLFWwindow *m_window;
    GameState m_state;
    std::unique_ptr<Snake> m_snake;
    std::unique_ptr<Food> m_food;
    std::unique_ptr<Border> m_border;
    
    // ----- Private Game functions -----
    void addFood();
    void checkCollision();
};
