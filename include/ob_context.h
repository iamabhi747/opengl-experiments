#ifndef OB_CONTEXT_H
#define OB_CONTEXT_H

// Just for the proper highlighting
// It will be ignored by the preprocessor
// #include <ob.h>

struct OB_Context
{
#ifdef OB_ENABLE_SHADER
    std::vector<GLfloat> Vertices;
    std::vector<GLuint>  Elements;

// OB_ENABLE_SHADER
#endif
};

OB_Context *OB_InitContext();

// OB_CONTEXT_H
#endif