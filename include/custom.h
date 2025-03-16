#ifndef CUSTOM_H
#define CUSTOM_H
#include <ob.h>

void DDA_Line(int x0, int y0, int x1, int y1);
void Breseham_Line(int x0, int y0, int x1, int y1);
void Midpoint_Circle(int xc, int yc, int r);
void Breseham_Circle(int xc, int yc, int r);
void Midpoint_Ellipse(int xc, int yc, int rx, int ry);

void IdentityMatrix2D(GLfloat transformationMatrix[3][3]);
void Rotate2D(GLfloat transformationMatrix[3][3], GLfloat angle, GLfloat cx, GLfloat cy);
void Scale2D(GLfloat transformationMatrix[3][3], GLfloat sx, GLfloat sy, GLfloat cx, GLfloat cy);
void Translate2D(GLfloat transformationMatrix[3][3], GLfloat tx, GLfloat ty);
void Shear2D(GLfloat transformationMatrix[3][3], GLfloat shx, GLfloat shy, GLfloat cx, GLfloat cy);
void ReflectX2D(GLfloat transformationMatrix[3][3], GLfloat cy);
void ReflectY2D(GLfloat transformationMatrix[3][3], GLfloat cx);
void ApplyTransformation2D(GLfloat transformationMatrix[3][3], GLfloat *x, GLfloat *y);
void Transform2D_thread(OB_Context *context, GLfloat *vertices, GLint size);
void ApplyTransformation2D(GLfloat transformationMatrix[3][3], GLfloat *vertices, GLint size);

void IdentityMatrix3D(GLfloat transformationMatrix[4][4]);
void Translate3D(GLfloat transformationMatrix[4][4], GLfloat tx, GLfloat ty, GLfloat tz);
void Scale3D(GLfloat transformationMatrix[4][4], GLfloat sx, GLfloat sy, GLfloat sz, GLfloat cx, GLfloat cy, GLfloat cz);
void RotateX3D(GLfloat transformationMatrix[4][4], GLfloat angle, GLfloat cx, GLfloat cy, GLfloat cz);
void RotateY3D(GLfloat transformationMatrix[4][4], GLfloat angle, GLfloat cx, GLfloat cy, GLfloat cz);
void RotateZ3D(GLfloat transformationMatrix[4][4], GLfloat angle, GLfloat cx, GLfloat cy, GLfloat cz);
void ReflectXY3D(GLfloat transformationMatrix[4][4], GLfloat cz);
void ReflectYZ3D(GLfloat transformationMatrix[4][4], GLfloat cx);
void ReflectXZ3D(GLfloat transformationMatrix[4][4], GLfloat cy);
void ApplyTransformation3D(GLfloat transformationMatrix[4][4], GLfloat *x, GLfloat *y, GLfloat *z);
void ApplyTransformation3D(GLfloat transformationMatrix[4][4], GLfloat *vertices, GLint size);
void Transform3D_thread(OB_Context *context, GLfloat *vertices, GLint size);

// CUSTOM_H
#endif