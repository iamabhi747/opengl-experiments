#include <custom.h>

void secondaryCircle(int xc, int yc)
{
    Breseham_Circle(xc, yc, 160);
}

void OB_VarInit(OB_Context *context)
{
    context->i = 0;
    context->j = 0;
    context->k = 1;
}

void OB_Render(OB_Context *context)
{
    glColor3f(0.0, 1.0, 0.0);
    for (int i = (context->i % 20) / 2; i < 360; i += 10)
    {
        Breseham_Circle(600 + 200 * cos(i * 3.14159 / 180), 450 + 200 * sin(i * 3.14159 / 180), 160);
    }

    glColor3f(1.0, 0.0, 0.0);
    for (int i = 40; i > 1; i -= 10)
    {
        Breseham_Circle(600, 450, i);
        Breseham_Circle(600, 450, i-1);
    }
    Breseham_Circle(600, 450, 360);
    Breseham_Circle(600, 450, 361);

    Breseham_Circle(600, 450, 360 + context->j);

    context->i++;
    context->j += context->k;
    if (context->j > 30 || context->j < 1)
    {
        context->k *= -1;
    }
}