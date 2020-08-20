//drawScene.h - draws the scene for assignment 2
//Connor Nicholson
//16 May 20


#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include <GL/freeglut.h>
#include "animation.h"

void onScreenText(void);
void drawSunset(void);
void drawBall1(void);

extern GLfloat p1[3];
extern GLfloat p2[3];
extern GLfloat p3[3];
extern GLfloat p4[3];
extern GLfloat p5[3];
extern GLfloat p6[3];
void drawPlanes(void);
void calcNormal(GLfloat *a, GLfloat *b, GLfloat *c);
void drawPlane1(void);
void drawPlane2(void);
void drawAxis(void);


#endif // DRAWSCENE_H
