#ifndef OB_CONTEXT_H
#define OB_CONTEXT_H

// Just for the proper highlighting
// It will be ignored by the preprocessor
// #include <ob.h>

struct OB_Color
{
    float r, g, b, a;
};

struct OB_Point
{
    float x, y;
};

struct OB_Context
{
#ifdef OB_ENABLE_SHADER
    std::vector<GLfloat> Vertices;
    std::vector<GLuint>  Elements;

// OB_ENABLE_SHADER
#endif

    // GLFW Window
    GLFWwindow *window;

    // Screenshot
    bool captureFrame;
    std::string screenshotPath;

    GLfloat pointsize = 3.0f;

    //// General Purpose Variables
    // Counters
    int i, j, k, l, m, n;
    // Angles
    float angle1, angle2, angle3, angle4;
    // Colors
    OB_Color col1, col2, col3, col4, col5, col6, col7, col8;
    // Sizes
    float size1, size2, size3, size4, size5, size6, size7, size8;
    // Positions
    OB_Point pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10;
    
};

void OB_VarInit(OB_Context *ctx);
OB_Context *OB_InitContext();

// OB_CONTEXT_H
#endif