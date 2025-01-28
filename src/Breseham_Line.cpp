#include <custom.h>
#include <math.h>

// Breseham Line Drawing Algorithm
// x0, y0: Starting point
// x1, y1: Ending point
// Draws a line from (x0, y0) to (x1, y1)
// Time Complexity: O(max(|dx|, |dy|))
// Space Complexity: O(1)
// Works in Draw mode [GL_POINTS]

void Breseham_Line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x = x0;
    int y = y0;
 
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
 
    if (dx > dy) {
        int p = 2 * dy - dx;
        for (int i = 0; i < dx; i++) {
            glVertex2f(x, y);
            while (p >= 0) {
                p = p - 2 * dx;
                y = y + sy;
            }
            p = p + 2 * dy;
            x = x + sx;
        }
    } else {
        int p = 2 * dx - dy;
        for (int i = 0; i < dy; i++) {
            glVertex2f(x, y);
            while (p >= 0) {
                p = p - 2 * dy;
                x = x + sx;
            }
            p = p + 2 * dx;
            y = y + sy;
        }
    }
}