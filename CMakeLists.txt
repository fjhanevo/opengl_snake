cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(opengl_snake)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


# ----- Executables ------ 
add_executable(opengl_snake
    src/main.cpp
    src/external/glad.c
)

target_include_directories(opengl_snake PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include         # for header files
    ${CMAKE_CURRENT_SOURCE_DIR}/libs            # for external header files
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(opengl_snake PRIVATE OpenGL::GL glfw)
