#include <custom.h>

OB_Context *OB_InitContext()
{
    OB_Context *context = new OB_Context();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background to black
    glOrtho(0.0, 800, 0.0, 600, -1.0, 1.0); // Set orthographic projectio

#ifdef OB_ENABLE_SHADER

    // Vertex data for triangle
    context->Vertices = {
        +0.0f,  0.5f,
        +0.5f, -0.5f,
        -0.5f, -0.5f
    };
    // Elements for triangle
    context->Elements = {
        0, 1, 2
    };

#endif

    return context;
}