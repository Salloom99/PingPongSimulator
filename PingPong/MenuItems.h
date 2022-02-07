#ifndef MENUITEMS_H
#define MENUITEMS_H


#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "Menu.h"
#include "Objects.h"
#include "IMGLoader.h"


void mainMenu();
void aboutCustom();
void physicsCustom();
void exitCustomFunc();
void exitGame();
void physicsMenu();
void options();

float oldGravity;
float gravity;
float p;
pixel *img;
int camera_mode;
int exitMenu;
int info;

float racket_speed;

int fullscreen;
int autokick;
	
int menuSelect;
int gameIsPaused;

int sideViewEnabled;

int screen_height;
int screen_width;


#endif