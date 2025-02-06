#ifndef OB_H
#define OB_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>

#define OB_DEBUG
// #define OB_ENABLE_SHADER

#include <ob_context.h>

#define OB_DRAW_MODE GL_POINTS
void OB_Render(OB_Context *context);
bool OB_SaveScreenshot(std::string filepath, OB_Context *context);
void OB_CaptureFrame(std::string filepath, OB_Context *context);

#ifdef OB_ENABLE_SHADER
#define OB_FRAGSHADER_PATH "shaders/fg_default.glsl"
#define OB_VERTSHADER_PATH "shaders/vt_default.glsl"

// OB_ENABLE_SHADER
#endif

// OB_H
#endif
