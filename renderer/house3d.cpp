#include <custom.h>
#include <thread>


void OB_VarInit(OB_Context *context)
{
    // Vertices
    context->m = 3 * 14;
    context->fptr1 = new GLfloat[context->m]{
        350, 300,  200, /*0*/
        850, 300,  200, /*1*/
        350, 600,  200, /*2*/
        850, 600,  200, /*3*/
        350, 300, -200, /*4*/
        850, 300, -200, /*5*/
        350, 600, -200, /*6*/
        850, 600, -200, /*7*/
        350, 750,    0, /*8*/
        850, 750,    0, /*9*/
        400, 300,  200, /*10*/
        550, 300,  200, /*11*/
        400, 550,  200, /*12*/
        550, 550,  200, /*13*/
    };

    // Lines
    context->l = 2 * 20;
    context->uptr1 = new GLuint[context->l]{
        0, 1, 1, 3, 3, 2, 2, 0,
        4, 5, 5, 7, 7, 6, 6, 4,
        0, 4, 1, 5, 2, 6, 3, 7,
        8, 9, 2, 8, 6, 8, 3, 9,
        7, 9,
        10, 12, 11, 13, 12, 13,
    };

    float transformationMatrix[4][4];
    IdentityMatrix3D(transformationMatrix);
    Translate3D(transformationMatrix, 0, 50, 0);
    ApplyTransformation3D(transformationMatrix, context->fptr1, context->m);
    RotateX3D(transformationMatrix, -0.02, 600, 450, 0);
    ApplyTransformation3D(transformationMatrix, context->fptr1, context->m);
    RotateY3D(transformationMatrix, 0.1, 600, 450, 0);
    ApplyTransformation3D(transformationMatrix, context->fptr1, context->m);
    Scale3D(transformationMatrix, 0.6, 0.6, 0.6, 600, 450, 0);
    ApplyTransformation3D(transformationMatrix, context->fptr1, context->m);

    // start transformation thread
    std::thread t1(Transform3D_thread, context, context->fptr1, context->m);
    t1.detach();
}

void OB_Render(OB_Context *context)
{
    glEnd();
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, context->fptr1);

    float transformationMatrix[4][4];
    IdentityMatrix3D(transformationMatrix);
    RotateY3D(transformationMatrix, 0.01, 600, 450, 0);
    ApplyTransformation3D(transformationMatrix, context->fptr1, context->m);
    
    glLineWidth(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glDrawElements(GL_LINES, context->l, GL_UNSIGNED_INT, context->uptr1);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glBegin(OB_DRAW_MODE);
}