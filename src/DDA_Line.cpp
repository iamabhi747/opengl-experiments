#include <custom.h>
#include <math.h>

// DDA Line Drawing Algorithm
// x0, y0: Starting point
// x1, y1: Ending point
// Draws a line from (x0, y0) to (x1, y1)
// Time Complexity: O(max(|dx|, |dy|))
// Space Complexity: O(1)
// Works in Draw mode [GL_POINTS]

void DDA_Line(int x0, int y0, int x1, int y1) {

    int dx = x1 - x0;
    int dy = y1 - y0;
 
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
 
    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;
 
    float x = x0;
    float y = y0;
 
    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y); // Plot the point
        x += xIncrement;
        y += yIncrement;
    }
}