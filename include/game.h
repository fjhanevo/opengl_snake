#pragma once

#include "shader.h"
#include "snake.h"
#include "food.h"
#include "border.h"
#include <GLFW/glfw3.h>


enum GameState
{
    GAME_ACTIVE,
    GAME_LOST
};

class Game
{
public:
    // constructor and desctructor
    Game(GLuint width, GLuint height);
    ~Game();

    void run();
private:
    // ----- Member variables -----
    GLuint m_width{}, m_height{};
    GLuint m_score{};

    bool keys[1024];
    bool keysProcessed[1024];

    GLFWwindow *m_window;
    GameState m_state;
    Snake *m_snake;
    Food *m_food;
    Border *m_border;
    
    // ---- Game setup functions -----
    void init();
    void update(float dt);
    void render();
    void processInput();
    void cleanup();
    void playAgain();

    // ----- Game specific function
    void addFood();
    void checkCollision();
    float moveTimer {0.0f};
};
