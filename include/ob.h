#ifndef OB_H
#define OB_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define OB_DEBUG
// #define OB_ENABLE_SHADER

#include <ob_context.h>

#define OB_DRAW_MODE GL_POINTS
void OB_Render(OB_Context *context);

#ifdef OB_ENABLE_SHADER
#define OB_FRAGSHADER_PATH "shaders/fragment.glsl"
#define OB_VERTSHADER_PATH "shaders/vertex.glsl"

// OB_ENABLE_SHADER
#endif

// OB_H
#endif
