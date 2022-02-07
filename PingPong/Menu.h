#ifndef MENU_H
#define MENU_H

#include <string.h>
#include <stdarg.h>
#include <GL/glut.h>

#define MAX_MENU 10

int menuStartXY[2];
float menuHW[2];
int menuCount;
int menuEffect;
int selectedMenu;
int menuFade;
float factor;
float colour[3];
//void backObject;

enum MENU_EFFECTS {NO_EFFECT, MENU_FADE_EFFECT, etc};

void (*menuFuncArray[MAX_MENU])(void); //Array of function Pointers
void (*menuFuncPoint)(void); //Called when the menu is printed
char menuStringTxt[MAX_MENU][20]; //2 dimensional array of characters
void printTextXY(const char text[], float x, float y, int font);
void pressEnter();
void incrementSelectedMenu();
void decreaseSelectedMenu();
void pressRight();
void pressLeft();

void newMenu(int x, int y, float height, float wideltaTimeh, int effect, void *func);
void newMenuSelect(int x, int y, float height, float wideltaTimeh, int effect, void *func, int select);
void addMenuItem(const char text[], void *func);
void printMenu();
void printnl(char text[], float x, float y, int font, int spacing);
void printInfo(char text[], float x, float y, float info);
#endif