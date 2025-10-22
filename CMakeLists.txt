cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(opengl_snake)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


# ----- Executables ------ 
add_executable(opengl_snake
    src/main.cpp
)
