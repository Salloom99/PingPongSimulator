#include "MenuItems.h"


void customFunction()
{
	
	printnl("PING PONG SIMULATION", 450, screen_height - 150, 5, 15);
	printnl("\" I am standing when the ball comes, that's why I don't have to move. I can read the game. \"\n         - Jan-Ove Waldner", 200, screen_height -500, 7, 15);
	printnl("\" Being the best is not good enough. Try harder. Just make sure having fun is a central component of striving for excellence. \"\n         - Carl Horowitz", 200, screen_height-400, 7, 15);
	printnl("\" Table Tennis is like an atom. To the ignorant it is merely microscopic and insignificant in existance,\n but to the dedicated, it is intricate in design and the building block to everything we know. \"\n         - Matt Hetherington",  200, screen_height - 300, 7, 15);
	
}

void aboutCustom()
{
	char* text;
	text = "A simple simulation that consider air factors and impacts,\nyou can control the first player but the second player is automated with some moves\n done by me \"Salem Domani\"";
	glColor3f(0.0, 0.0, 0.0);
	printnl(text, 100, 430, 7, 15);
}

void exitCustomFunc()
{
	printnl("Are you sure you want to exit?", screen_width- 300, screen_height -500, 8, 15);
}

void exitGame()
{
	exitMenu = 1;
	newMenu(screen_width- 300, screen_height -600, 30.0, 100.0, 1, exitCustomFunc);
	addMenuItem("No", mainMenu);
	addMenuItem("Yes", exit);
}

void fullScreen() {
	fullscreen = !fullscreen;
}

void enableDisableGrav()
{
	if (gravity == 0)
		gravity = oldGravity;
	else
	{
		oldGravity = gravity;
		gravity = 0;
	}
	
	menuSelect = 1;

	options();
}

void changeCameraMode()
{
	camera_mode++;
	if (camera_mode > 5)
		camera_mode = 0;

	menuSelect = 0;
	options();
}

void physicsCustom() 
{
	glColor3f(0.0, 0.0, 0.0);
	char* text = "- F = m.a \n- a = dv/dt \n- Vt = Vo + a.dt \n- Vt = Vo + F/m * dt \n";
	printnl(text, 500, 550, 5, 30);
}

void physicsMenu()
{
	newMenu(screen_width- 300, 20, 30.0, 100.0, 1, physicsCustom);
	addMenuItem("Back", mainMenu);
}


void controlsCustom()
{
	glColor3f(0.0, 0.0, 0.0);
	char* text = "0 - Camera mode0 (Default View)\n1 - Camera mode1 (Closer View)\n2 - Camera mode2 (Opponent View) \n3 - Camera mode3 (Right View)\n4 - Camera mode4 (Left View) \n5 - Camera mode5 (Rotation View)\n \nW - Moves the racket Forwards\nS - Moves the Racket Backwards\nD - Moves the racket to the right\nA - Moves the racket to the left\nSpace - Slow down the racket\n \nR - Resets the ball\nB - Ball Setup\nV - Rotated hit\nN - Normal Serve\nK - Autokick mode\n \nM & R - Reset ball's mass\nM & - - Decrease ball's mass\nM & + - Increase ball's mass\nG & R - Reset Gravity\nG & - - Decrease Gravity\nG & + - Increase Gravity\nP & R - Reset Air density\nP & - - Decrease Air density\nP & + - Increase Air density\n \nI - Display informations\nEsc - Pauses the game";
	printnl(text, 100, 550, 7, 15);
}

void controlsMenu()
{
	newMenu(screen_width- 300, 20, 30.0, 100.0, 1, controlsCustom);
	addMenuItem("Back", mainMenu);

}

void options()
{
	char camera_mode1[30];
	char gravityON[30];
	char* grav = gravity != 0 ? "ON" : "OFF";


	newMenuSelect(screen_width- 300, screen_height- 500, 30.0, 100.0, 1, customFunction, menuSelect);
	sprintf(camera_mode1, "Camera View : %d", camera_mode);
	addMenuItem(camera_mode1, changeCameraMode);
	addMenuItem("Full Screen", fullScreen);
	sprintf(gravityON, "Gravity : %s", grav);
	addMenuItem(gravityON, enableDisableGrav);

	addMenuItem("Back", mainMenu);
}

void about()
{
	newMenu(screen_width- 300, 20, 30.0, 100.0, 1, aboutCustom);
	addMenuItem("Back", mainMenu);
}

void startGame()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.29, 0.46, 0.83, 0);
	gameIsPaused = 0;
	glutReshapeWindow(1366,720);
}

void mainMenu()
{
	
	menuSelect = 0;
	exitMenu = 0;
	newMenu(screen_width-300, screen_height-500, 30.0, 100.0, 1, customFunction);
	addMenuItem("Start Simulation", startGame);
	addMenuItem("Physics", physicsMenu);
	addMenuItem("Controls", controlsMenu);
	addMenuItem("Options", options);
	addMenuItem("About", about);
	addMenuItem("Exit", exitGame);
}