# OpenGl Exercises and Experiments

This is a collection of OpenGL exercises and experiments. The goal is to learn and understand OpenGL by doing experiments and exercises.
This project is templeted from my base templete [opengl-base](https://github.com/iamabhi747/opengl-base)

## Experiment Categories
- Understanding drawing algorithms (for lines, circles, bezier curves, etc) using Drawmode with GL_POINTS
- Understanding transformations

## Experiments
- Default Blank Window
- Lines using DDA & Bresenham Algorithm
- Circles using Midpoint & Bresenham Algorithm
- Circle Art: Illusive pattern using circles
- Ellipses using Midpoint Algorithm
- Ellipse Art: Toyota Logo using ellipses
- Rook 2D: Rook using trangles & lines, demonstrating 2D transformations

## Algorithms
- DDA Line Drawing Algorithm
- Bresenham Line Drawing Algorithm
- Midpoint Circle Drawing Algorithm
- Breseham Circle Drawing Algorithm
- Midpoint Ellipse Drawing Algorithm
- 2D Transformations (Translation, Rotation, Scaling, Shearing, Reflection)

>### ✅ tested on macos

## Repository Structure
- `src/` - Contains the source code for the various algorithms
- `renderer/` - Contains the source code for the experiments done using Draw mode (each file is a seperate renderer [expreriment])
- `shaders/` - Contains the shaders for the experiments done using Shader mode
- `include/` - Contains the header files base setup

## Getting Started

### Prerequisites (macos)
```bash
brew install glfw3 glew
```

### To switch between Draw Mode and Shader Mode
comment / uncomment out the `#define OB_ENABLE_SHADER` in `include/ob.h` to switch between Draw Mode and Shader Mode

### To Select the Experiment in Draw Mode
update the RENDERER variable in `Makefile` to the file name of the renderer you want to run

### To Select the Experiment in Shader Mode
update the shaders name in `include/ob.h` to the shaders you want to run

### To Take Screenshot
call OB_CaptureFrame(filepath, context), it will save the current frame to the filepath


### Build & Run
```bash
make
```
or

Run task `Build & Run` in vscode (cmd + shift + b)