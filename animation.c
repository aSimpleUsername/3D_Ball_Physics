#include "animation.h"

/*********************************
        OBJECT MOVEMENT
**********************************/
float startTime;
float prevTime;

typedef GLfloat point3[3];

float dropOff = 0.90;      // speed will drop 90% at each bounce

float gravity = -9.8;
float gravMultiplier = 1;
point3 gravVel = {0, 0, 0};  // initialise, gravity is assigned later

// Ball 1
point3 ball1StartPos = {10, 10, 10};	// the initial position
point3 b1, ball1PrevPos;	// the current and previous location of the centre of the ball
point3 ball1ThrowVel ={0, 0, 0}; 		// initial velocity - set to 0 in all directions
point3 ball1CurrVel, ball1PrevVel; 		// current and previous velocity
float ball1YRotationAngle = 0.0f;
float b1Radius = 1.0f;
float throwForce = 10;

void animate(void)
{
    glutTimerFunc(TIMERSECS, animate, 0);

    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0 ;     // to convert the returned into seconds
    float timeSincePrevFrame = currTime - prevTime;	// time since previous frame


    // Calculate all the forces that are currently applied to the ball

    // Calculate acceleration
    // In our case, it is just the gravity g

    gravVel[1] = gravity * gravMultiplier;


    // Move one step
    b1[0] = ball1PrevPos[0] + ball1PrevVel[0] * timeSincePrevFrame + ball1ThrowVel[0] + gravVel[0] * timeSincePrevFrame * timeSincePrevFrame / 2;
    b1[1] = ball1PrevPos[1] + ball1PrevVel[1] * timeSincePrevFrame + ball1ThrowVel[1] + gravVel[1] * timeSincePrevFrame * timeSincePrevFrame / 2;
    b1[2] = ball1PrevPos[2] + ball1PrevVel[2] * timeSincePrevFrame + ball1ThrowVel[2] + gravVel[2] * timeSincePrevFrame * timeSincePrevFrame / 2;

    // Calculate current velocity
    ball1CurrVel[0] = ball1PrevVel[0] + ball1ThrowVel[0] + gravVel[0] * timeSincePrevFrame;
    ball1CurrVel[1] = ball1PrevVel[1] + ball1ThrowVel[1] + gravVel[1] * timeSincePrevFrame;
    ball1CurrVel[2] = ball1PrevVel[2] + ball1ThrowVel[2] + gravVel[2] * timeSincePrevFrame;

    // Check collision plane 1
    checkCollision(p1, p2, p3);
    // Check collision plane 2
    checkCollision(p1, p2, p5);

 // Put curPos to prevPos
    ball1PrevPos[0] = b1[0];
    ball1PrevPos[1] = b1[1];
    ball1PrevPos[2] = b1[2];

    ball1PrevVel[0] = ball1CurrVel[0];
    ball1PrevVel[1] = ball1CurrVel[1];
    ball1PrevVel[2] = ball1CurrVel[2];

    prevTime = currTime;
}

void checkCollision(GLfloat *c1, GLfloat *c2, GLfloat *c3)       //bad variable names, but 3 collision points
{
    float v1[3], v2[3], v[3], n[3];
    float vm, nm, d;        //vector magnitude, normal magnitude, distance

    //p1 to p2 vector
    v1[0] = c2[0] - c1[0];
    v1[1] = c2[1] - c1[1];
    v1[2] = c2[2] - c1[2];
    //p1 to p3 vector
    v2[0] = c3[0] - c1[0];
    v2[1] = c3[1] - c1[1];
    v2[2] = c3[2] - c1[2];
    //cross product
    v[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v[2] = v1[0]*v2[1] - v1[1]*v2[0];
    //vector magnitude
    vm =  sqrt( pow(v[0], 2) + pow(v[1],2) + pow(v[2],2));
    //normal vector
    n[0] = v[0] / vm;
    n[1] = v[1] / vm;
    n[2] = v[2] / vm;
    //normal magnitude
    nm = sqrt( pow(n[0], 2) + pow(n[1],2) + pow(n[2],2));
    //distance = absolute dot product of p1 -> b1 and normal, divide normal magnitude
    d = abs((b1[0]-c1[0])*n[0] + (b1[1]-c1[1])*n[1] + (b1[2]-c1[2])*n[2]) / nm;

    if(d <= b1Radius)
        rebound(n, nm);
}

void rebound(float *n, float nm)  //reflection accross normal vector
{
    float un[3];    //unit normal vector
    un[0] = n[0] / nm;
    un[1] = n[0] / nm;
    un[2] = n[0] / nm;

    float dotProd = n[0]*ball1CurrVel[0] + n[1]*ball1CurrVel[1] + n[2]*ball1CurrVel[2];

    ball1CurrVel[0] = (ball1CurrVel[0] - 2*dotProd*n[0]) * dropOff;
    ball1CurrVel[1] = (ball1CurrVel[1] - 2*dotProd*n[1]) * dropOff;
    ball1CurrVel[2] = (ball1CurrVel[2] - 2*dotProd*n[2]) * dropOff;
}

void rotateZAxis(float angle)
{
    float xTemp;

    xTemp = p1[0];
    p1[0] = cos(angle) * p1[0] - sin(angle) * p1[1];
    p1[1] = sin(angle) * xTemp + cos(angle) * p1[1];

    xTemp = p2[0];
    p2[0] = cos(angle) * p2[0] - sin(angle) * p2[1];
    p2[1] = sin(angle) * xTemp + cos(angle) * p2[1];

    xTemp = p3[0];
    p3[0] = cos(angle) * p3[0] - sin(angle) * p3[1];
    p3[1] = sin(angle) * xTemp + cos(angle) * p3[1];

    xTemp = p4[0];
    p4[0] = cos(angle) * p4[0] - sin(angle) * p4[1];
    p4[1] = sin(angle) * xTemp + cos(angle) * p4[1];

    xTemp = p5[0];
    p5[0] = cos(angle) * p5[0] - sin(angle) * p5[1];
    p5[1] = sin(angle) * xTemp + cos(angle) * p5[1];

    xTemp = p6[0];
    p6[0] = cos(angle) * p6[0] - sin(angle) * p6[1];
    p6[1] = sin(angle) * xTemp + cos(angle) * p6[1];
}

void rotateXAxis(float angle)
{
    float zTemp;

    zTemp = p1[2];
    p1[2] = cos(angle) * p1[2] - sin(angle) * p1[1];
    p1[1] = sin(angle) * zTemp + cos(angle) * p1[1];

    zTemp = p2[2];
    p2[2] = cos(angle) * p2[2] - sin(angle) * p2[1];
    p2[1] = sin(angle) * zTemp + cos(angle) * p2[1];

    zTemp = p3[2];
    p3[2] = cos(angle) * p3[2] - sin(angle) * p3[1];
    p3[1] = sin(angle) * zTemp + cos(angle) * p3[1];

    zTemp = p4[2];
    p4[2] = cos(angle) * p4[2] - sin(angle) * p4[1];
    p4[1] = sin(angle) * zTemp + cos(angle) * p4[1];

    zTemp = p5[2];
    p5[2] = cos(angle) * p5[2] - sin(angle) * p5[1];
    p5[1] = sin(angle) * zTemp + cos(angle) * p5[1];

    zTemp = p6[2];
    p6[2] = cos(angle) * p6[2] - sin(angle) * p6[1];
    p6[1] = sin(angle) * zTemp + cos(angle) * p6[1];
}

void resetObjects(void)
{
    // Ball 1
    b1[0] = ball1StartPos[0];
    b1[1] = ball1StartPos[1];
    b1[2] = ball1StartPos[2];

    ball1PrevPos[0] = ball1StartPos[0];
    ball1PrevPos[1] = ball1StartPos[1];
    ball1PrevPos[2] = ball1StartPos[2];

    ball1PrevVel[0] = 0;
    ball1PrevVel[1] = 0;
    ball1PrevVel[2] = 0;

    ball1CurrVel[0] = 0;
    ball1CurrVel[1] = 0;
    ball1CurrVel[2] = 0;

    ball1ThrowVel[0] = 0;
    ball1ThrowVel[1] = 0;
    ball1ThrowVel[2] = 0;
}
