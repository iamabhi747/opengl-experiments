#include <custom.h>

__attribute__((weak)) void OB_VarInit(OB_Context *ctx)
{
    // Empty Implementation
    // Implement & Override this function in renderer when needed
}

OB_Context *OB_InitContext()
{
    OB_Context *context = new OB_Context();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background to black
    glOrtho(0.0, 1200, 0.0, 900, -450, 450); // Set orthographic projectio

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

    OB_VarInit(context);

    return context;
}