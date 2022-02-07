#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>
#include <GL/glut.h>
#include "glm.h"

typedef float vector3Df[3];
typedef float vector2Df[2];
typedef int vector2Di[2];

typedef struct
{
	GLfloat location[3];
	GLfloat oldLocation[3];
	GLfloat velocity[3];
	GLfloat mass;
	GLfloat rotation[2];
	GLfloat radius;
	GLfloat friction;
	GLfloat reboundFactor;
	GLfloat bounds[3];
}obj;

obj ball;
obj racket;


typedef struct
{
	GLfloat center[3];
	GLfloat dimentions[3];
	GLfloat mass;
	GLfloat reboundFactor;
	GLfloat friction;
}rect3D;

rect3D net;
rect3D table;

void drawRoom();
void drawShadows();
void drawRacketShadow();
void drawBallShadow();
void drawBall();
void drawRacket(float x, float y, float z);
void drawTable();
void drawTableLegs();
void drawLeg(int leg_x, int leg_z);
void drawNet();
void drawCircle(float cx, float cy, float cz, float r, int num_segments);
#endif