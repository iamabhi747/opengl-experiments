#include <custom.h>

void mc_drawOctateMirrorPoints(int x, int y, int xc, int yc)
{
    glVertex2f(xc + x, yc + y);
    glVertex2f(xc - x, yc + y);
    glVertex2f(xc + x, yc - y);
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc + y, yc + x);
    glVertex2f(xc - y, yc + x);
    glVertex2f(xc + y, yc - x);
    glVertex2f(xc - y, yc - x);
}

// Mid-Point Circle Drawing Algorithm
void Midpoint_Circle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 1 - r;
    mc_drawOctateMirrorPoints(x, y, xc, yc);
    while (y > x)
    {
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        mc_drawOctateMirrorPoints(x, y, xc, yc);
    }
}