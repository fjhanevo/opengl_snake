#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "constants.h"
#include "game.h"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);


// Create the Game instance here
Game Snake(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);

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

    // tell GLFW to associate the game instance with the window
    glfwSetWindowUserPointer(window, &Snake);

    // ----- Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

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
        glfwPollEvents();

        // User input
        Snake.processInput();

        // update Game state
        Snake.update(deltaTime);
        // Render a background
        glClearColor(0.0f, 0.4f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // render
        Snake.render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ||
    key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key <= 1024)
        {
        if (action == GLFW_PRESS)
            Snake.m_keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            Snake.m_keys[key] = false;
            Snake.m_keysProcessed[key] = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
   glViewport(0,0 , width, height);
}
