#include <custom.h>

void bc_drawOctateMirrorPoints(int x, int y, int xc, int yc)
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

// Breseham Circle Drawing Algorithm
void Breseham_Circle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    bc_drawOctateMirrorPoints(x, y, xc, yc);
    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }

        bc_drawOctateMirrorPoints(x, y, xc, yc);
    }
}