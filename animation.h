//animation.h - animation for assignment 2
//Connor Nicholson
//16 May 20

#ifndef ANIMATION_H
#define ANIMATION_H

#include <GL/freeglut.h>
#include <math.h>

#include "drawScene.h"

#define TIMERSECS 1000/60   //ms in a seccond / frames per seccond


extern float startTime;
extern float prevTime;
typedef GLfloat point3[3];

extern float dropOff;      // speed will drop with 30% at each bounce

extern float gravity;
extern float gravMultiplier;        //100% earth gravity
extern point3 gravVel;	// this is the acceleration

// Ball 1
extern point3 ball1StartPos;	// the initial position
extern point3 b1, ball1PrevPos;	// the current and previous location of the centre of the ball
extern point3 ball1ThrowVel; 		// initial velocity - set to 0 in all directions
extern point3 ball1CurrVel, ball1PrevVel; 		// current and previous velocity
extern float ball1YRotationAngle;
extern float b1Radius;
extern float throwForce;



/****************************************************************/

void animate(void);

void resetObjects(void);
//c1 = collision point 1
void checkCollision(GLfloat *c1, GLfloat *c2, GLfloat *c3);
void rebound(float *n, float nm); //normal vector

void rotateZAxis(float angle);
void rotateXAxis(float angle);




#endif
