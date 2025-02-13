#ifndef CUSTOM_H
#define CUSTOM_H
#include <ob.h>

void DDA_Line(int x0, int y0, int x1, int y1);
void Breseham_Line(int x0, int y0, int x1, int y1);
void Midpoint_Circle(int xc, int yc, int r);
void Breseham_Circle(int xc, int yc, int r);
void Midpoint_Ellipse(int xc, int yc, int rx, int ry);

// CUSTOM_H
#endif