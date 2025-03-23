#include <custom.h>
#include <math.h>

void getPolygonVertices(GLfloat *vertices, int n, float r, float startAngle, float cx, float cy)
{
    float angle = 2 * M_PI / n;
    for (int i = 0; i < n; i++)
    {
        vertices[i * 2 + 0] = cx + r * cos(startAngle + i * angle);
        vertices[i * 2 + 1] = cy + r * sin(startAngle + i * angle);
    }
}

void OB_VarInit(OB_Context *context)
{
    context->fptr1 = new GLfloat[48 * 2];

    context->size1 = 400;
    getPolygonVertices(&context->fptr1[0], 8, context->size1, -M_PI_2, 600, 450);

    context->size2 = -(context->fptr1[3] - 450) / cos(M_PI_4 / 2);
    getPolygonVertices(&context->fptr1[16], 8, context->size2, -3 * M_PI_4 / 2, 600, 450);

    context->size3 = -(context->fptr1[3] - 450);
    getPolygonVertices(&context->fptr1[32], 8, context->size3, -M_PI_2, 600, 450);

    context->size4 = -(context->fptr1[35] - 450) / cos(M_PI_4 / 2);
    getPolygonVertices(&context->fptr1[48], 8, context->size4, -3 * M_PI_4 / 2, 600, 450);

    context->size5 = 50;
    getPolygonVertices(&context->fptr1[64], 16, context->size5, -M_PI_2, 600, 450);

    context->l = 48 * 2;
    context->uptr1 = new GLuint[context->l];
    for (int i = 0; i < 8; i++)
    {
        context->uptr1[i * 2 + 0] = i;
        context->uptr1[i * 2 + 1] = i + 8;

        context->uptr1[(i + 8) * 2 + 0] = i + 16;
        context->uptr1[(i + 8) * 2 + 1] = i == 7 ? 0 : i + 1;

        context->uptr1[(i + 16) * 2 + 0] = i;
        context->uptr1[(i + 16) * 2 + 1] = i * 2 + 32;

        context->uptr1[(i + 24) * 2 + 0] = i + 16;
        context->uptr1[(i + 24) * 2 + 1] = i + 24;

        context->uptr1[(i + 32) * 2 + 0] = i + 24;
        context->uptr1[(i + 32) * 2 + 1] = i == 7 ? 16 : i + 17;

        context->uptr1[(i + 40) * 2 + 0] = i + 24;
        context->uptr1[(i + 40) * 2 + 1] = i * 2 + 33;
    }

    context->col1 = OB_Color(255, 255, 255, 255);
    context->col2 = OB_Color(0, 0, 255, 255);
    context->col3 = OB_Color(255, 255, 0, 255);
    context->col4 = OB_Color(0, 255, 0, 255);
    context->col5 = OB_Color(150, 255, 150, 255);
    context->col6 = OB_Color(255, 100, 30, 255);
    context->col7 = OB_Color(255, 130, 80, 255);
    context->col8 = OB_Color(255, 60, 200, 255);
}

void OB_Render(OB_Context *context)
{
    context->col1.setAsGLColor();
    Breseham_Circle(600, 450, context->size1);
    Breseham_Circle(600, 450, context->size5);
    Breseham_Circle(600, 450, context->size5 - 15);

    glEnd();
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, context->fptr1);
    context->col1.setAsGLColor();

    glLineWidth(5.0);
    glDrawElements(GL_LINES, context->l, GL_UNSIGNED_INT, context->uptr1);

    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
    std::vector<GLubyte> pixels = GetPixels(context);

    FloodFill(600, 450, context->col2, context->col1, pixels, context->width / 2, context->height / 2);
    FloodFill(600 + context->size5 - 5, 450, context->col3, context->col1, pixels, context->width / 2, context->height / 2);

    float angle = 2 * M_PI / 8;
    for (int i = 0; i < 8; i++)
    {
        FloodFill(
            600 + context->size4 * cos(i * angle + M_PI_4 / 4),
            450 + context->size4 * sin(i * angle + M_PI_4 / 4),
            context->col4, context->col1,
            pixels, context->width / 2, context->height / 2
        );

        FloodFill(
            600 + context->size4 * cos(i * angle + 3 * M_PI_4 / 4),
            450 + context->size4 * sin(i * angle + 3 * M_PI_4 / 4),
            context->col5, context->col1,
            pixels, context->width / 2, context->height / 2
        );

        FloodFill(
            600 + context->size3 * cos(i * angle + M_PI_4 / 2),
            450 + context->size3 * sin(i * angle + M_PI_4 / 2),
            context->col6, context->col1,
            pixels, context->width / 2, context->height / 2
        );

        FloodFill(
            600 + (context->size1 - 10) * cos(i * angle + M_PI_4 / 2),
            450 + (context->size1 - 10) * sin(i * angle + M_PI_4 / 2),
            context->col8, context->col1,
            pixels, context->width / 2, context->height / 2
        );
    }

    RenderPixels(context, pixels);
    glBegin(OB_DRAW_MODE);
}