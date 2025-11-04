# OpenGL Snake Game

A classic Snake game built from scratch using C++20 and OpenGL.

## Built with
* **C++20** 
* **OpenGL (via GLAD)** for rendering
* **GLFW** for window creation and input
* **GLM** for vector/matrix math
* **FreeType** for font loading and text rendering
* **'stb_image'** for loading textures


## Dependencies 
* GLFW
* FreeType

### Arch
```bash
sudo pacman -Syu glfw freetype2
```

### Ubuntu
```bash
sudo apt-get install -y libglfw3-dev libfreetype-dev
```

### macOS
```bash
brew install glfw freetype
```

## Build Steps
1. **Clone the repo:**
```bash
git clone https://github.com/fjhanevo/opengl_snake
cd opengl_snake
```

2. **Create and navigate to the build directory:**
```bash
mkdir build
cd build
```

3. **Run CMake to configure the project:**
```bash
cmake ..
```
4. **Compile the project:**
```bash
make
```
*(Or `cmake --build .`)

5. **Run the game**
```bash
./opengl_snake
```

