//lighting.c - implementation of lighting.h
//Connor Nicholson
//17 Jun 20

#include "lighting.h"


void enableLighting()
{
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void lighting()
{
    GLfloat lightPos[] = {30, 20, 60, 0};
    GLfloat specularMaterial[] = {1.0, 1.0, 1.0};
    GLfloat specularShine[] = {120};
    GLfloat diffuseLight[] = {1.0, 1.0, 1.0};
    GLfloat specularLight[] = {1.0, 1.0, 1.0};
    GLfloat ambientLight[] = {1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, specularShine);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    GL_SMOOTH;
}
