#include "Menu.h"


/*
 * Same as newMenu, except that this has an extra parameter to select a specific menu item
 * The first menu is selected by default for newMenu.
*/
void newMenuSelect(int x, int y, float height, float width, int effect, void *func, int select) 
{
	newMenu(x, y, height, width, effect, func);
	selectedMenu = select; //Select a menu
}

/*
 * Empties/Prepaires for a new menu
*/
void newMenu(int x, int y, float height, float width, int effect, void *func)
{
	menuStartXY[0] = x;
	menuStartXY[1] = y;

	menuHW[0] = height;
	menuHW[1] = width;

	menuEffect = effect;
	menuCount = 0;
	selectedMenu = 0;
	menuFade = 1;
	factor = 0;
	colour[0] = 0.0;
	colour[1] = 0.0;
	colour[2] = 0.0;

	menuFuncPoint = func;
}

// Adds a new menu item, only needs to be called once per menu item.
void addMenuItem(const char text[], void *func)
{
	if(menuCount < MAX_MENU)
	{
		menuFuncArray[menuCount] = func; //The Function to call when the menu item is clicked/selected
		strcpy(menuStringTxt[menuCount], text); //Copy the text for the menu
		menuCount++;
	}
}

void incrementSelectedMenu() { selectedMenu++; }
void decreaseSelectedMenu() { selectedMenu--; }

void pressEnter()
{
	//previousMenu
	(*menuFuncArray[selectedMenu])(); //Excute the specific function that corresponds to the selected text.
}

void pressRight() {
	factor++;
}

void pressLeft() {
	factor--;
}

void printTextXY(const char text[], float x, float y, int font)
{
	glRasterPos2f(x, y);
	for (int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font, text[i]);
}

void printnl(char text[], float x, float y, int font, int spacing)
{
	char *pch;
	char *str = strdup(text);

	pch = strtok (str,"\n");

	while (pch != NULL)
	{
		printTextXY(pch, x, y-=spacing, font);

		pch = strtok (NULL, "\n");
	}
}

void printInfo(char text[], float x, float y, float info)
{
	x -= 0.5;
	char* str = strdup(text);
	char str2[100];
	sprintf(str2, str, info);
	printnl(str2,x,y,2,0);


}

// a basic rectange to indicate a selected menu item.
void rectangle()
{
    glBegin(GL_QUADS);
        glVertex2f(0.0,		0.0);
        glVertex2f(0.0,		32.0);
		glVertex2f(200.0,	32.0);
		glVertex2f(200.0,	0.0);
	glEnd();	
}

///This is called in the display, it prints the menu items.
void printMenu()
{
	static float lastTime = 0.0f, presentTime = 0.0f;
	int i,j;
	float fade = 0.0;
	float tp;

	presentTime = glutGet(GLUT_ELAPSED_TIME);

	tp = (presentTime - lastTime);

	
	fade = 0.0006 * tp;

	if(tp > 1000)
		fade = 0.01;

	lastTime = presentTime;

	(*menuFuncPoint)(); //Excute The Function
	//(*menuFuncArray[selectedMenu])();

	if(selectedMenu >= menuCount) { selectedMenu = 0; }
	else if (selectedMenu <= -1) { selectedMenu = menuCount-1; }


	for(i = 0; i < menuCount; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		if(selectedMenu == i)
		{
			for(j = 0; j < 3; j++)
			{
				if(colour[j] >= 1.0){ menuFade = 0; } 
				else if(colour[j] <= 0.0){ menuFade = 1; }

				if(menuFade){ colour[j]+=fade; }//Need to fix this so that it depends on time...
				else{ colour[j]-=fade; }
			}
			
			glColor3f(colour[0], colour[1], colour[2]); //Selected menu item Fade
			printTextXY(menuStringTxt[i],  menuStartXY[0], menuStartXY[1]-(i*30), (int)GLUT_BITMAP_TIMES_ROMAN_24);	//Printing it here, prints it on top of the box (DEPTH TESTING MUST ENABLED)

			//Draw / Fade Box arround the selected menu item
			glColor3f(1.0-colour[0], 1.0-colour[1], 1.0-colour[2]);
			glPushMatrix();
				glTranslated(menuStartXY[0]-10, menuStartXY[1]-10-(i*30), 0.0);
				rectangle();
			glPopMatrix();
		}
		else
		{
			printTextXY(menuStringTxt[i],  menuStartXY[0], menuStartXY[1]-(i*30), (int)GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}
