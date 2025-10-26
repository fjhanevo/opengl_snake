#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "constants.h"
#include "game.h"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(
        Constants::SCREEN_WIDTH, 
        Constants::SCREEN_HEIGHT,
        "Snake", nullptr, nullptr
    );

    glfwMakeContextCurrent(window);


    // ----- Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ----- Create the Game object -----
    Game Snake(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, window);

    // tell GLFW to associate the game instance with the window
    glfwSetWindowUserPointer(window, &Snake);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ----- OpenGL config -----
    glViewport(0, 0,Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ----- Initialize the game -----
    Snake.init();
    float deltaTime{ 0.0f };
    float lastFrame{ 0.0f };

    // main loop 
    while (!glfwWindowShouldClose(window))
    {
        // Calculate deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // User input
        Snake.processInput();
        glfwPollEvents();

        // Update Game state
        Snake.update(deltaTime);

        // Render
        Snake.render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    // Get the Game instance 
    Game* game {static_cast<Game*>(glfwGetWindowUserPointer(window))};
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ||
    key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key <= 1024)
        {
        if (action == GLFW_PRESS)
            game->m_keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            game->m_keys[key] = false;
            game->m_keysProcessed[key] = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // Get the Game instance
    Game *game{ static_cast<Game*>(glfwGetWindowUserPointer(window))};
    if (game)
    {
        game->m_width = width;
        game->m_height = height;
        glViewport(0,0 , width, height);
    }
}
