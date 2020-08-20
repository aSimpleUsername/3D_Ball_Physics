#include "userInput.h"

const int true = 1;
const int false = 0;


/****************************
        CAMERA
****************************/

float angle=0;
float angle1 = 0;
// actual vector representing the camera's direction
float lx = 0;
float ly = 0;       //default values just to start looking where I want
float lz = 0;
// XYZ position of the camera
float xc = 30;
float yc = 20;
float zc = 60;
float speed = 0.1;

/*************************
        MOUSE
*************************/
float xrotSpeed = 0.0005f;    //mouse sensitivity
float yrotSpeed = 0.0004f;    //mouse sensitivity
int mx, my;
int lmbPressed = 0;        //left mouse button pressed = false

void mouseMovement(int x, int y)
{
    mx = x;     //mouse x
    my = y;     //mouse y
}

void mouseClick(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        lmbPressed = true;
    else
        lmbPressed = false;
}


void processMouse(void)
{
    glutWarpPointer((1920/2), (1080/2));

    if(lmbPressed)
    {
        b1[0] = xc -2;
        b1[1] = yc -1;
        b1[2] = zc -2;

        ball1PrevPos[0] = xc;
        ball1PrevPos[1] = yc;
        ball1PrevPos[2] = zc;

        ball1CurrVel[0] = 0;
        ball1CurrVel[1] = 0;
        ball1CurrVel[2] = 0;

        ball1PrevVel[0] = -10;
        ball1PrevVel[1] = 5;
        ball1PrevVel[2] = -15;
    }

}


/**************************
        KEYBOARD
**************************/

int* keyStates[256];    //array of 'booleans'
int* specialKeyStates[256];     //array of 'booleans'

int ballTrack = 0;  //false4

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true;     //set the key to pressed
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = false;     //set the key to released
}

void specialKeyPressed(int key, int x, int y)
{
    specialKeyStates[key] = true;
}

void specialKeyUp(int key, int x, int y)
{
    specialKeyStates[key] = false;
}

void processKeys(void)
{
    if(keyStates[27])      //escape key
        exit(0);
    if(keyStates['R'] || keyStates['r'])       //press R to reset
    {
        resetObjects();
    }

    if(keyStates['W'] || keyStates['w'])      //move planes up
    {
        p1[1] += 0.1;
        p2[1] += 0.1;
        p3[1] += 0.1;
        p4[1] += 0.1;
        p5[1] += 0.1;
        p6[1] += 0.1;
    }

    if(keyStates['S'] || keyStates['s'])      //move planes down
    {
        p1[1] -= 0.1;
        p2[1] -= 0.1;
        p3[1] -= 0.1;
        p4[1] -= 0.1;
        p5[1] -= 0.1;
        p6[1] -= 0.1;
    }
    if(keyStates['D'] || keyStates['d'])      //move planes right
    {
        p1[0] += 0.1;
        p2[0] += 0.1;
        p3[0] += 0.1;
        p4[0] += 0.1;
        p5[0] += 0.1;
        p6[0] += 0.1;
    }
    if(keyStates['A'] || keyStates['a'])      //move planes left
    {
        p1[0] -= 0.1;
        p2[0] -= 0.1;
        p3[0] -= 0.1;
        p4[0] -= 0.1;
        p5[0] -= 0.1;
        p6[0] -= 0.1;
    }

    if(specialKeyStates[GLUT_KEY_UP])
        rotateXAxis(0.02f);

    if(specialKeyStates[GLUT_KEY_DOWN])
        rotateXAxis(-0.02f);

    if(specialKeyStates[GLUT_KEY_LEFT])
        rotateZAxis(0.02f);

    if(specialKeyStates[GLUT_KEY_RIGHT])
        rotateZAxis(-0.02f);

    if(keyStates['Z'])   //if 'k' scale increases
        b1Radius += 0.05f;
    if(keyStates['z'])   //if 'j' scale decreases
        b1Radius -= 0.05f;

    if(keyStates['c'])
        ballTrack = true;
    if(keyStates['C'])
        ballTrack = false;

    if(keyStates['i'])
        printf("WORKED\n");

}
