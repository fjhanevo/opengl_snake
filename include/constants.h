#pragma once
#include <glad/glad.h>

namespace Constants
{
    constexpr GLuint SCREEN_WIDTH   { 800 }; 
    constexpr GLuint SCREEN_HEIGHT  { 600 }; 
    constexpr GLuint GRID_SIZE      { 40 };
    // Normalization constants
    constexpr GLuint ROWS           { SCREEN_WIDTH / GRID_SIZE };
    constexpr GLuint COLS           { SCREEN_HEIGHT / GRID_SIZE };
}
