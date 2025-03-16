#include <math.h>
#include <custom.h>

void IdentityMatrix3D(GLfloat transformationMatrix[4][4])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transformationMatrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void Translate3D(GLfloat transformationMatrix[4][4], GLfloat tx, GLfloat ty, GLfloat tz)
{
    transformationMatrix[0][3] = tx;
    transformationMatrix[1][3] = ty;
    transformationMatrix[2][3] = tz;
}

void Scale3D(GLfloat transformationMatrix[4][4], GLfloat sx, GLfloat sy, GLfloat sz, GLfloat cx, GLfloat cy, GLfloat cz)
{
    transformationMatrix[0][0] = sx;
    transformationMatrix[1][1] = sy;
    transformationMatrix[2][2] = sz;
    transformationMatrix[0][3] = cx * (1 - sx);
    transformationMatrix[1][3] = cy * (1 - sy);
    transformationMatrix[2][3] = cz * (1 - sz);
}

void RotateX3D(GLfloat transformationMatrix[4][4], GLfloat angle, GLfloat cx, GLfloat cy, GLfloat cz)
{
    GLfloat cosA = cos(angle);
    GLfloat sinA = sin(angle);
    transformationMatrix[1][1] = cosA;
    transformationMatrix[1][2] = -sinA;
    transformationMatrix[2][1] = sinA;
    transformationMatrix[2][2] = cosA;
    transformationMatrix[1][3] = cy - cy * cosA + cz * sinA;
    transformationMatrix[2][3] = cz - cy * sinA - cz * cosA;
}

void RotateY3D(GLfloat transformationMatrix[4][4], GLfloat angle, GLfloat cx, GLfloat cy, GLfloat cz)
{
    GLfloat cosA = cos(angle);
    GLfloat sinA = sin(angle);
    transformationMatrix[0][0] = cosA;
    transformationMatrix[0][2] = sinA;
    transformationMatrix[2][0] = -sinA;
    transformationMatrix[2][2] = cosA;
    transformationMatrix[0][3] = cx - cx * cosA - cz * sinA;
    transformationMatrix[2][3] = cz + cx * sinA - cz * cosA;
}

void RotateZ3D(GLfloat transformationMatrix[4][4], GLfloat angle, GLfloat cx, GLfloat cy, GLfloat cz)
{
    GLfloat cosA = cos(angle);
    GLfloat sinA = sin(angle);
    transformationMatrix[0][0] = cosA;
    transformationMatrix[0][1] = -sinA;
    transformationMatrix[1][0] = sinA;
    transformationMatrix[1][1] = cosA;
    transformationMatrix[0][3] = cx - cx * cosA + cy * sinA;
    transformationMatrix[1][3] = cy - cx * sinA - cy * cosA;
}

void ReflectXY3D(GLfloat transformationMatrix[4][4], GLfloat cz)
{
    transformationMatrix[2][2] = -1;
    transformationMatrix[2][3] = 2 * cz;
}

void ReflectYZ3D(GLfloat transformationMatrix[4][4], GLfloat cx)
{
    transformationMatrix[0][0] = -1;
    transformationMatrix[0][3] = 2 * cx;
}

void ReflectXZ3D(GLfloat transformationMatrix[4][4], GLfloat cy)
{
    transformationMatrix[1][1] = -1;
    transformationMatrix[1][3] = 2 * cy;
}

void ApplyTransformation3D(GLfloat transformationMatrix[4][4], GLfloat *x, GLfloat *y, GLfloat *z)
{
    GLfloat x1 = *x;
    GLfloat y1 = *y;
    GLfloat z1 = *z;
    *x = transformationMatrix[0][0] * x1 + transformationMatrix[0][1] * y1 + 
         transformationMatrix[0][2] * z1 + transformationMatrix[0][3];
    *y = transformationMatrix[1][0] * x1 + transformationMatrix[1][1] * y1 + 
         transformationMatrix[1][2] * z1 + transformationMatrix[1][3];
    *z = transformationMatrix[2][0] * x1 + transformationMatrix[2][1] * y1 + 
         transformationMatrix[2][2] * z1 + transformationMatrix[2][3];
}

void ApplyTransformation3D(GLfloat transformationMatrix[4][4], GLfloat *vertices, GLint size)
{
    for (int i = 0; i < size; i += 3) {
        ApplyTransformation3D(transformationMatrix, &vertices[i], &vertices[i + 1], &vertices[i + 2]);
    }
}