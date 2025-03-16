#include <math.h>
#include <custom.h>

void IdentityMatrix2D(GLfloat transformationMatrix[3][3])
{
    transformationMatrix[0][0] = 1;
    transformationMatrix[0][1] = 0;
    transformationMatrix[0][2] = 0;
    transformationMatrix[1][0] = 0;
    transformationMatrix[1][1] = 1;
    transformationMatrix[1][2] = 0;
    transformationMatrix[2][0] = 0;
    transformationMatrix[2][1] = 0;
    transformationMatrix[2][2] = 1;
}

void Rotate2D(GLfloat transformationMatrix[3][3], GLfloat angle, GLfloat cx, GLfloat cy)
{
    GLfloat cosA = cos(angle);
    GLfloat sinA = sin(angle);
    transformationMatrix[0][0] = cosA;
    transformationMatrix[0][1] = -sinA;
    transformationMatrix[0][2] = cx - cx * cosA + cy * sinA;
    transformationMatrix[1][0] = sinA;
    transformationMatrix[1][1] = cosA;
    transformationMatrix[1][2] = cy - cx * sinA - cy * cosA;
}

void Scale2D(GLfloat transformationMatrix[3][3], GLfloat sx, GLfloat sy, GLfloat cx, GLfloat cy)
{
    transformationMatrix[0][0] = sx;
    transformationMatrix[0][2] = cx * (1 - sx);
    transformationMatrix[1][1] = sy;
    transformationMatrix[1][2] = cy * (1 - sy);
}

void Translate2D(GLfloat transformationMatrix[3][3], GLfloat tx, GLfloat ty)
{
    transformationMatrix[0][2] = tx;
    transformationMatrix[1][2] = ty;
}

void Shear2D(GLfloat transformationMatrix[3][3], GLfloat shx, GLfloat shy, GLfloat cx, GLfloat cy)
{
    transformationMatrix[0][1] = shx;
    transformationMatrix[0][2] = -shx * cy;
    transformationMatrix[1][0] = shy;
    transformationMatrix[1][2] = -shy * cx;
}

void ReflectX2D(GLfloat transformationMatrix[3][3], GLfloat cy)
{
    transformationMatrix[1][1] = -1;
    transformationMatrix[1][2] = 2 * cy;
}

void ReflectY2D(GLfloat transformationMatrix[3][3], GLfloat cx)
{
    transformationMatrix[0][0] = -1;
    transformationMatrix[0][2] = 2 * cx;
}

void ApplyTransformation2D(GLfloat transformationMatrix[3][3], GLfloat *x, GLfloat *y)
{
    GLfloat x1 = *x;
    GLfloat y1 = *y;
    *x = transformationMatrix[0][0] * x1 + transformationMatrix[0][1] * y1 + transformationMatrix[0][2];
    *y = transformationMatrix[1][0] * x1 + transformationMatrix[1][1] * y1 + transformationMatrix[1][2];
}

void ApplyTransformation2D(GLfloat transformationMatrix[3][3], GLfloat *vertices, GLint size)
{
    for (int i = 0; i < size; i += 3) {
        ApplyTransformation2D(transformationMatrix, &vertices[i], &vertices[i + 1]);
    }
}
