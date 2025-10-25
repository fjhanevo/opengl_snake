cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(opengl_snake)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# for resource path
configure_file(config.h.in config.h)

# ----- Executables ------ 
add_executable(opengl_snake
    src/main.cpp
    src/game.cpp
    src/snake.cpp
    src/food.cpp
    src/border.cpp
    src/external/glad.c
    src/external/shader.cpp
    src/external/texture.cpp
    src/external/sprite_renderer.cpp
    src/external/resource_manager.cpp
)

target_include_directories(opengl_snake PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include         # for header files
    ${CMAKE_CURRENT_SOURCE_DIR}/libs            # for external header files
    ${CMAKE_BINARY_DIR}                         # make config.h visible
)

target_link_libraries(opengl_snake PRIVATE OpenGL::GL glfw)
