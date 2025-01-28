#include <custom.h>

void OB_Render(OB_Context *context)
{
    glColor3f(1.0, 0.0, 0.0);
    DDA_Line(100, 100, 1100, 800);
    DDA_Line(100, 700, 1000, 100);

    glColor3f(0.0, 1.0, 0.0);
    Breseham_Line(100, 800, 1100, 100);
    Breseham_Line(200, 100, 1100, 700);
}