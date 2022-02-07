#ifndef COLLISION_H
#define COLLISION_H

#include <stdlib.h>
#include "gl/glut.h"
#include "Objects.h"
#include <stdio.h>

int didCollide(	obj *sphere, const float location[3], const float XYZ[3]);
int collision(obj *temp, obj* temp2);
int collision2(obj* temp, rect3D rect);
void collisionDetection();
void ballBounds();
void racketBounds(float x1, float x2, float z1, float z2);
#endif