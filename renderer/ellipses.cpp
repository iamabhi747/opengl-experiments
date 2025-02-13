#include <custom.h>

void OB_Render(OB_Context *context)
{
    // Draw Ellipses
    glColor3f(1.0, 0.0, 0.0);
    Midpoint_Ellipse(600, 450, 100, 200);
    glColor3f(0.0, 0.0, 1.0);
    Midpoint_Ellipse(600, 450, 200, 100);
}