# OpenGl Base structure

this is a base structure for opengl projects

Can be run in 2 modes:
- Shader mode: uses shaders to render a triangle
- Draw mode: uses opengl functions to render POINTS, LINES, TRIANGLES, etc.. (default)

Switch between modes by commeting / uncommeting the `OB_ENABLE_SHADERS` in the `include/ob.h` file

DEBUG mode is enabled by default, to disable it, comment `OB_DEBUG` in the `include/ob.h` file

## USAGE
- Impliment the `void OB_InitContext()` function in the `src/init.cpp` file to initialize your context
- Implement the `void OB_Render()` function in the `src/render.cpp` file to use Draw mode
- Implement the fragment and vertex shaders in the `shaders` folder to use Shader mode
- Also add data in context.Vertices and context.Elements in the `OB_InitContext()` function to use Shader mode

✅ tested on macos

## Getting Started

### Prerequisites (macos)
```bash
brew install glfw3 glew
```

### Build & Run
```bash
make
```
or

Run task `Build & Run` in vscode (cmd + shift + b)