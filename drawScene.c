#include "drawScene.h"

void onScreenText(void)
{
    glColor3f(1.0, 1.0, 1.0);
    GLdouble width = 1920;
    GLdouble height = 1080;
    float x = 5, y = 20, z = 0;
    char text[16][50] = {
        {"CONTROLS:\0"},
        {"\0"},
        {"LMB Throw ball\0"},
        {"A/a: Board moves to the left\0"},
        {"D/d: Board moves to the right\0"},
        {"W/w: Board moves up\0"},
        {"S/s: Board moves down\0"},
        {"LEFT: Rotate anticlockwise on Z axis\0"},
        {"RIGHT: Rotate clockwise on Z axis\0"},
        {"UP: Rotate clockwise on X axis\0"},
        {"DOWN Rotate anticlockwise on X axis\0"},
        {"z: Decrease size of ball\0"},
        {"Z: Increase size of ball\0"},
        {"c: Track ball\0"},
        {"C: Look at origin\0"},
        {"R/r: Reset ball\0"},
    };
    for(int i=0; i<16; i++)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glLoadIdentity();
        glRasterPos3f(x, y+(20*i), z);
        char *c;
        for(c=text[i]; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        glPopMatrix();

        //restore Perspective projection
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

}

void drawBall1(void)
{
    glPushMatrix();
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //set colour of bone
    glTranslatef(b1[0], b1[1], b1[2]);
    glScalef(b1Radius, b1Radius, b1Radius);    //bone can size up or down
    glutSolidSphere(b1Radius, 25, 30);
    glLoadIdentity();
    glPopMatrix();
}

GLfloat p1[3] = {0, 0, 50};
GLfloat p2[3] = {0, 0, -50};
GLfloat p3[3] = {25, 0, 50};
GLfloat p4[3] = {25, 0, -50};
GLfloat p5[3] = {0, 25, 50};
GLfloat p6[3] = {0, 25, -50};
GLfloat normal[3];

void drawPlanes(void)
{
    glPushMatrix();
    drawPlane1();
    drawPlane2();
    glLoadIdentity();
    glPopMatrix();
}

void calcNormal(GLfloat *a, GLfloat *b, GLfloat *c)
{
    float v1[3], v2[3], v[3], n;
    // a to b vector
    v1[0] = b[0] - a[0];
    v1[1] = b[1] - a[1];
    v1[2] = b[2] - a[2];
    // a to c vector
    v2[0] = b[0] - c[0];
    v2[1] = b[1] - c[1];
    v2[2] = b[2] - c[2];
    //cross product
    v[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v[2] = v1[0]*v2[1] - v1[1]*v2[0];

    n = (sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
    normal[0] = v[0]/n;
    normal[1] = v[1]/n;
    normal[2] = v[2]/n;
}

void drawPlane1(void)
{
        glColor4f(0.10f, 0.51f, 0.71f, 1.0f); //set colou
        //trianlge1
        calcNormal(p1 , p2, p3);
        glBegin(GL_TRIANGLES);
        glNormal3fv(normal);
        glVertex3fv(p1);
        glVertex3fv(p2);
        glVertex3fv(p3);
        glEnd();
        //triangle 2
        calcNormal(p3, p2, p4);
        glBegin(GL_TRIANGLES);
        glNormal3fv(normal);
        glVertex3fv(p3);
        glVertex3fv(p2);
        glVertex3fv(p4);
        glEnd();

}

void drawPlane2(void)
{
        glColor4f(0.49f, 0.83f, 0.92f, 1.0f); //set colou
        //trianlge1
        calcNormal(p1, p2, p5);
        glBegin(GL_TRIANGLES);
        glNormal3fv(normal);
        glVertex3fv(p1);
        glVertex3fv(p5);
        glVertex3fv(p2);
        glEnd();
        //triangle 2
        calcNormal(p5, p6, p2);
        glBegin(GL_TRIANGLES);
        calcNormal(p1, p2, p5);
        glVertex3fv(p5);
        glVertex3fv(p6);
        glVertex3fv(p2);
        glEnd();
}

void drawAxis(void)
{
    glPushMatrix();

    glLineWidth(2.0);
    //x axis
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(-50, 0, 0);
    glVertex3f(50, 0, 0);
    glEnd();
    //y axis
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);
    glEnd();
    //z axis
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0, 0, -50);
    glVertex3f(0, 0, 50);
    glEnd();

    glLoadIdentity();
    glPopMatrix();
}
