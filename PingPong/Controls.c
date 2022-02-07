#include "Controls.h"


void kbSpecialFunc(int key, int x, int y)
{
	if(gameIsPaused)
	{
		switch(key)
		{
		case GLUT_KEY_DOWN:
			incrementSelectedMenu();
			break;

		case GLUT_KEY_UP:
			decreaseSelectedMenu();
			break;

		case GLUT_KEY_LEFT:
			pressLeft();
			break;

		case GLUT_KEY_RIGHT:
			pressRight();
			break;
		}
	}
}

void kbUp(unsigned char key, int x, int y)
{
	keys[(int)tolower(key)] = 0;
}

void kbDown(unsigned char key, int x, int y)
{
	keys[(int)tolower(key)] = 1;
}

void mouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && exitMenu == 1)
	{
		if(x >= 250 && y >= 130 && x <= 450 && y <= 380)
			exit(0);
	}
}

void checkKeyPressed()
{
	
	if(gameIsPaused)
	{
		if(keys[13]) //Enter
		{
			pressEnter();
			keys[13] = 0;
		}

	}
	else
	{
		///-------------------------------------<Camera modes>
		if (keys[(int)'0'])
		{
			camera_mode = 0;
		}
		if (keys[(int)'1'])
		{
			camera_mode = 1;
		}
		if (keys[(int)'2'])
		{
			camera_mode = 2;
		}
		if (keys[(int)'3'])
		{
			camera_mode = 3;
		}
		if (keys[(int)'4'])
		{
			camera_mode = 4;
		}
		if (keys[(int)'5'])
		{
			camera_mode = 5;
		}
		///-------------------------------------<Racket movements>
		if(keys[(int)'w'])
		{
			racket.velocity[2] -= racket_speed;
		}

		if(keys[(int)'s'])
		{
			racket.velocity[2] += racket_speed;
		}

		if(keys[(int)'d'])
		{
			racket.velocity[0] += racket_speed;
		}

		if(keys[(int)'a'])
		{
			racket.velocity[0] -= racket_speed;
		}
		

		if(keys[(int)' '])
		{
			racket.velocity[0] -= racket.velocity[0] * 0.01;
			racket.velocity[2] -= racket.velocity[2] * 0.01;
		}
		///-------------------------------------<Ball movements>
		if(keys[(int)'r'] && !keys[(int)'g'])
		{
			resetBall();
		}

		if(keys[(int)'b'])
		{
			ballBounce();
		}

		if (keys[(int)'v'])
		{
			rotatedHit();
		}

		if (keys[(int)'n'])
		{
			NormalServe();
		}
		///-------------------------------------<Physics controls>
		if(keys[(int)'g'] && keys[(int)'-'])
		{
			
			gravity-= 0.5;
			keys[(int)'-'] = 0;
		}

		if(keys[(int)'g'] && keys[(int)'='])
		{
			gravity+= 0.5;
			keys[(int)'='] = 0;
		}

		
		if(keys[(int)'g'] && keys[(int)'r'] && !keys[(int)'='] && !keys[(int)'-'])
		{
			gravity =  9.8;
		}

		if (keys[(int)'m'] && keys[(int)'-'])
		{

			ball.mass -= 1;
			keys[(int)'-'] = 0;
		}

		if (keys[(int)'m'] && keys[(int)'='])
		{
			ball.mass += 1;
			keys[(int)'='] = 0;
		}


		if (keys[(int)'m'] && keys[(int)'r'] && !keys[(int)'='] && !keys[(int)'-'])
		{
			ball.mass = 20;
		}

		if (keys[(int)'p'] && keys[(int)'-'])
		{

			p -= 0.1;
			keys[(int)'-'] = 0;
		}

		if (keys[(int)'p'] && keys[(int)'='])
		{
			p += 0.1;
			keys[(int)'='] = 0;
		}


		if (keys[(int)'p'] && keys[(int)'r'] && !keys[(int)'='] && !keys[(int)'-'])
		{
			p = 1.2;
		}
		if (keys[(int)'i'])
		{
			info = !info;
			keys[(int)'i'] = 0;
		}
		if (keys[(int)'k'])
		{
			autokick = !autokick;
			keys[(int)'k'] = 0;
		}

		if (keys[(int)'f'])
		{
			fullscreen = !fullscreen;
			keys[(int)'k'] = 0;
		}
		
		if(keys[27]) //Esc
		{
			pauseGame();
			mainMenu();
			keys[27] = 0;
		}
	}

}
