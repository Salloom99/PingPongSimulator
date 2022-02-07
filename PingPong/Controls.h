#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdlib.h>
#include "gl/glut.h" 
#include "Menu.h"
#include <ctype.h>
#include "Objects.h"
#include "MenuItems.h"

int keys[256]; //An array to keep track of keys pressed 


void kbSpecialFunc(int key, int x, int y);
void kbUp(unsigned char key, int x, int y);
void kbDown(unsigned char key, int x, int y);
void checkKeyPressed();
void mouseFunc(int button, int state, int x, int y);

#endif