#include <custom.h>
#include <thread>


void OB_VarInit(OB_Context *context)
{
    // Vertices
    context->m = 3 * 32;
    context->fptr1 = new GLfloat[context->m]{
        500, 375, 0, /*0*/      700, 375, 0, /*1*/      700, 525, 0, /*2*/      500, 525, 0, /*3*/
        700, 560, 0, /*4*/      500, 560, 0, /*5*/      740, 560, 0, /*6*/      460, 560, 0, /*7*/
        735, 350, 0, /*8*/      465, 350, 0, /*9*/      735, 320, 0, /*10*/     465, 320, 0, /*11*/
        765, 290, 0, /*12*/     435, 290, 0, /*13*/     765, 240, 0, /*14*/     435, 240, 0, /*15*/
        740, 590, 0, /*16*/     460, 590, 0, /*17*/     736, 560, 0, /*18*/     464, 560, 0, /*19*/
        736, 590, 0, /*20*/     464, 590, 0, /*21*/     740, 650, 0, /*22*/     460, 650, 0, /*23*/
        680, 590, 0, /*24*/     520, 590, 0, /*25*/     680, 650, 0, /*26*/     520, 650, 0, /*27*/
        630, 590, 0, /*28*/     570, 590, 0, /*29*/     630, 650, 0, /*30*/     570, 650, 0, /*31*/
    };

    // Triangles
    context->n = 3 * 14;
    context->uptr1 = new GLuint[context->n]{
        0, 1, 4, 0, 4, 5, 
        3, 5, 7, 
        2, 6, 4, 
        11, 10, 8, 11, 8, 9, 
        15, 14, 12, 15, 12, 13, 
        16, 24, 26, 16, 26, 22, 
        25, 17, 23, 25, 23, 27, 
        29, 28, 30, 29, 30, 31
    };

    // Lines
    context->l = 2 * 7;
    context->uptr2 = new GLuint[context->l]{
        9, 0,
        8, 1,
        10, 12,
        11, 13,
        16, 17,
        18, 20,
        19, 21,
    };

    // start transformation thread
    std::thread t1(Transform2D_thread, context, context->fptr1, context->m);
    t1.detach();
}

void OB_Render(OB_Context *context)
{
    glEnd();
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, context->fptr1);
    glColor3f(1.0, 0.0, 0.0);

    glDrawElements(GL_TRIANGLES, context->n, GL_UNSIGNED_INT, context->uptr1);
    
    glLineWidth(30.0);
    glDrawElements(GL_LINES, context->l, GL_UNSIGNED_INT, context->uptr2);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glBegin(OB_DRAW_MODE);
}