#include <custom.h>
#include <iostream>

void GetWidthHeight(OB_Context *context)
{
    glfwGetFramebufferSize(context->window, &context->width, &context->height);
}

std::vector<GLubyte> GetPixels(OB_Context *context)
{
    // Allocate memory for the pixel data
    std::vector<GLubyte> pixels(context->width * context->height * 4); // 4 components (RGBA)

    // Read pixels from framebuffer
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, context->width, context->height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    // Flip the image vertically since OpenGL has a different coordinate system
    std::vector<GLubyte> flipped(context->width * context->height * 4);
    for (int y = 0; y < context->height; y++) {
        memcpy(&flipped[(context->height - 1 - y) * context->width * 4],
               &pixels[y * context->width * 4],
               context->width * 4);
    }

    return flipped;
}

void RenderPixels(OB_Context *context, std::vector<GLubyte>& pixels)
{
    int width = context->width, height = context->height;

    // Create a texture to render the pixels
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload the pixel data to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    width /= 2;
    height /= 2;

    // Render the texture
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -450, 450);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1, 0);
    glVertex2f(width, 0);
    glTexCoord2f(1, 1);
    glVertex2f(width, height);
    glTexCoord2f(0, 1);
    glVertex2f(0, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Cleanup
    glDeleteTextures(1, &texture);
}

int GetPixelIndex(int x, int y, int width)
{

    return (y * 2) * (width * 2 * 4) + (x * 2) * 4;
}

bool Check2Pixels(int x1, int y1, int x2, int y2, std::vector<GLubyte>& pixels, int width)
{
    int i1 = GetPixelIndex(x1, y1, width);
    int i2 = GetPixelIndex(x2, y2, width);
    for (int i = 0; i < 3; i++)
    {
        if (pixels[i1 + i] != pixels[i2 + i]) return false;
    }
    return true;
}

OB_Color getPixelColor(int x, int y, std::vector<GLubyte>& pixels, int width)
{
    int pi = GetPixelIndex(x, y, width);
    OB_Color pcolor;
    pcolor.r = pixels[pi + 0];
    pcolor.g = pixels[pi + 1];
    pcolor.b = pixels[pi + 2];
    pcolor.a = pixels[pi + 3];
    return pcolor;
}

void setPixelColor(int x, int y, OB_Color color, std::vector<GLubyte>& pixels, int width)
{
    int pi = GetPixelIndex(x, y, width);
    pixels[pi + 0] = color.r;
    pixels[pi + 1] = color.g;
    pixels[pi + 2] = color.b;
    pixels[pi + 3] = color.a;
}

bool Check2Colors(OB_Color c1, OB_Color c2)
{
    if (c1.r != c2.r || c1.g != c2.g || c1.b != c2.b) return false;
    return true;
}