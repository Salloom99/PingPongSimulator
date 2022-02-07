#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


#include "Objects.h"
#include "MenuItems.h"
#include "Controls.h"
#include "Collision.h"


///	-----------<Prototypes>--------------------
void resetBall();
void display(void);
void myReshape(int w, int h);
void camera();
void mouseFunc(int button, int state, int x, int y);
void pauseGame();
void idleFunc();
void RotateCamera(float speed);
void shiftCameraSmoothly(double x, double z);
///	===========</Prototypes>--------------------

double camera_x, camera_z, camera_distance, I;

void initializeVariables()
{
	screen_height = 1080;
	screen_width = 1920;
	fullscreen = 1;

	info = 0;
	autokick = 0;
	camera_distance = 50;
	camera_z = 50;
	I = 1;
	camera_mode = 0;

	gravity = 9.8;
	p = 1.2;

	sideViewEnabled = 0;
	racket_speed = 0.05;

	gameIsPaused = 1;
	exitMenu = 0;


	/// >---------------------------------------------<Racket>-------------------------------------------

	racket.radius = 20;
	racket.mass = 100;
	racket.reboundFactor = 1.0;

	racket.bounds[0] = 3.7;
	racket.bounds[1] = 2.2;
	racket.bounds[2] = 0.3;

	racket.location[0] = 0;
	racket.location[1] = 1;
	racket.location[2] = 20;

	racket.velocity[0] = 0;
	racket.velocity[1] = 0;
	racket.velocity[2] = 0;

	/// >---------------------------------------------<Ball>--------------------------------------------

	ball.location[0] = 0;
	ball.location[1] = 10;
	ball.location[2] = 0;

	ball.rotation[0] = 0;
	ball.rotation[1] = 0;

	ball.radius = 0.5;
	ball.mass = 20;

	/// >---------------------------------------------<Net>---------------------------------------------

	net.center[0] = 0;
	net.center[1] = 1.25;
	net.center[2] = 0;
	
	net.dimentions[0] = 26.0;
	net.dimentions[1] = 2.5;
	net.dimentions[2] = 0.4;

	net.reboundFactor = 0.2;

	/// >--------------------------------------------<Table>-------------------------------------------

	table.center[0] = 0;
	table.center[1] = -0.1;
	table.center[2] = 0;
	
	table.dimentions[0] = 26;
	table.dimentions[1] = 0.4;
	table.dimentions[2] = 52;

	table.reboundFactor = 0.8;


}

int main()
{
	initializeVariables();
	mainMenu();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

	glutInitWindowSize(1366, 720);
	
	glutCreateWindow( "Ping Pong Simulation" );
	glutReshapeFunc(myReshape);
	
	glutDisplayFunc(display);
		
	glClearColor(0.29, 0.46, 0.83, 0);

	glutSpecialFunc(kbSpecialFunc);
	glutKeyboardFunc(kbDown);
	glutKeyboardUpFunc(kbUp);
	glutIdleFunc(idleFunc);
	glutMouseFunc(mouseFunc);
	glutPositionWindow(100, 100);

	pauseGame();

	
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;
}

void camera()
{
	
	switch (camera_mode)
	{
	case 0:
		//------------------------------------Default View--------------------------------
		camera_x = 0;
		camera_z = 50;
		gluLookAt(0, 20, 60,
			0, 0, 0,
			0, 1, 0);
		break;
	case 1:
		//------------------------------------Front View--------------------------------
		shiftCameraSmoothly(0, 50);
		break;
	case 2:
		//------------------------------------Reversed View-------------------------------- 
		shiftCameraSmoothly(0, -50);
		break;
	case 3:
		//------------------------------------Right View--------------------------------
		shiftCameraSmoothly(50, 0);
		break;
	case 4:
		//------------------------------------Left View--------------------------------
		shiftCameraSmoothly(-50, 0);
		break;
	case 5:
		//-----------------------------------Rotaion View---------------------------------
		RotateCamera(0.01);
		gluLookAt(camera_x, 20, camera_z,
			0, 0, 0,
			0, 1, 0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	

	GLfloat mat_specular[] = { 1,1,1,1 };
	GLfloat mat_shininess[] = { 100.0 };
	GLfloat light1_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);

	checkKeyPressed();

	if(gameIsPaused)
	{
		glDisable(GL_LIGHTING);
		printMenu();
		glFlush();
		glutSwapBuffers();
		return;
	}

	
	camera();

	glEnable(GL_LIGHT0);
	drawBall();
	glDisable(GL_LIGHT0);
	drawShadows();
	drawTable();
	drawRoom();
	drawRacket(racket.location[0], racket.location[1], racket.location[2]);
	printingInfos();
	glFlush();
	
	glutSwapBuffers();

	return;
}

void myReshape(int width, int height)
{
	screen_height = height;
	screen_width = width;
	if (height==0) // prevent divide by zero
		height=1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (fullscreen)
		glutFullScreen();

	if(gameIsPaused)
	{
		gluOrtho2D(0.0,width, 0.0,height);
		glutReshapeWindow(width, height);
	}
	else
	{
		gluPerspective(45.0f,((GLfloat)width)/((GLfloat)height),0.01f,150.0f);
		glutReshapeWindow(width,height);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void idleFunc()
{
	static double lastTime, presentTime;
	
	presentTime = glutGet(GLUT_ELAPSED_TIME); 
	double deltaTime = (presentTime - lastTime) / 500; // because elapsed time in miliseconds + Our unit is too small
	lastTime = presentTime;

	if(gameIsPaused)
	{
		glutPostRedisplay();
		return;
	}


	for(int i=0; i<3;i++)
	{

		/// ----------<BALL>----------
		ball.oldLocation[i] = ball.location[i];
		ball.location[i] += deltaTime * ball.velocity[i];


		// F = m.a => a = F/m
		// fluid resistance
		ball.velocity[i] -= deltaTime * (0.5 * p * 0.49 * 3.14 * pow(ball.radius, 2) * ball.velocity[i] * ball.velocity[i] / ball.mass);
		/// ----------</BALL>----------

		

		/// ----------<RACKET>----------
		racket.oldLocation[i] = racket.location[i];
		racket.location[i] += deltaTime * racket.velocity[i];
		/// ----------</RACKET>----------
	}

	// rotational energy loss because of air resistance
	ball.rotation[0] -= ball.rotation[0] * 0.001;
	ball.rotation[1] -= ball.rotation[1] * 0.001;

	// float effect
	ball.velocity[1] -= deltaTime * (4.0 / 3.0 * M_PI * pow(ball.radius, 3) * p * gravity / ball.mass);

	// gravity effect
	// dv = a.dt => dv = -g.dt
	ball.velocity[1] -= deltaTime * gravity; 
	racket.velocity[1] -= deltaTime * gravity;

	// magnus effect
	ball.velocity[0] -= deltaTime * (8.0 / 3.0 * M_PI * pow(ball.radius, 3) * p * ball.velocity[2] * ball.rotation[0] / ball.mass);
	ball.velocity[1] -= deltaTime * (8.0 / 3.0 * M_PI * pow(ball.radius, 3) * p * ball.velocity[2] * ball.rotation[1] / ball.mass);

	// collisions
	collisionDetection();

	// the area can the racket move in 
	racketBounds(-15,15,5,35);

	// the area can the ball move in
	ballBounds();

	// autokick mode
	// if the ball is in range
	if (ball.location[1] > 0 &&
		ball.location[2] > racket.location[2] - 10 &&
		ball.location[2] < racket.location[2] - 0.3 &&
		ball.velocity[2] > 1)
	{

		float distZ = racket.location[2] - ball.location[2];
		float timeZ = ball.velocity[2] / distZ;
		float distY = ball.location[1] + ball.velocity[1] * timeZ + 0.5 * ball.velocity[1] * deltaTime;

		
			if (ball.location[0] > racket.location[0] - 2.5 &&
				ball.location[0] < racket.location[0] + 2.5)
				racket.velocity[1] = (distY - racket.location[1]) / timeZ;
		
		

		if(autokick)
		{
			float distX = ball.location[0] - racket.location[0];
			float timeY = ball.velocity[1] / gravity;
			racket.velocity[0] = 35 * distX / timeZ;
			racket.velocity[2] = ball.location[2] / -ball.velocity[2] + 1;
					
		}
		
	}
			
		
	
	// if the ball barely moving
	if (abs(ball.velocity[0]) <= 0.00001 &&
		abs(ball.velocity[1]) <= 0.00001 &&
		abs(ball.velocity[2]) <= 0.00001 &&
		ball.location[1] < 0)
			resetBall();
	


	glutPostRedisplay();
}

void NormalServe() {

	ball.location[0] = 0;
	ball.location[1] = 7;
	ball.location[2] = -30;

	ball.velocity[0] = 0;
	ball.velocity[1] = -8;
	ball.velocity[2] = 25;

	ball.rotation[0] = 0;
	ball.rotation[1] = 0;
}

void resetBall()
{

	ball.location[0] = 0;
	ball.location[1] = 7;
	ball.location[2] = -30;

	ball.velocity[0] = 0;
	ball.velocity[1] = 0;
	ball.velocity[2] = 50;

	ball.rotation[0] = 0;
	ball.rotation[1] = 0;
}


void ballBounce()
{
	ball.rotation[1] =  M_PI;

	ball.location[0] = 0;
	ball.location[1] = 10;
	ball.location[2] = 20;

	ball.velocity[0] = 0;
	ball.velocity[1] = 0;
	ball.velocity[2] = 0;

}


void rotatedHit()
{
	ball.rotation[0] = 4 * M_PI;
	ball.rotation[1] = 2 * M_PI;

	ball.location[0] = -10;
	ball.location[1] = 5;
	ball.location[2] = -20;

	ball.velocity[0] = 20;
	ball.velocity[1] = 12;
	ball.velocity[2] = 25;

}



void pauseGame()
{
	glClearColor(1,1,1, 0);
	gameIsPaused = 1;

	glutReshapeWindow(glutGet(GLUT_INIT_WINDOW_WIDTH) + 1, glutGet(GLUT_INIT_WINDOW_HEIGHT));
}

void RotateCamera(float speed) {

	if (camera_z <= camera_distance + 1 && camera_z >= 0 && I)
	{
		if (camera_z == camera_distance)
			I = !I;
		else
		{
			camera_z += speed;
			camera_x = sqrt(camera_distance * camera_distance - camera_z * camera_z);
		}
	}
	else if (camera_z <= 0 && camera_z >= -camera_distance - 1 && !I)
	{
		if (camera_z + camera_distance <= 0)
			I = !I;
		else
		{
			camera_z -= speed;
			camera_x = -sqrt(camera_distance * camera_distance - camera_z * camera_z);
		}
	}
	else if (camera_z <= 0 && camera_z >= -camera_distance - 1 && I)
	{

		camera_z += speed;
		camera_x = sqrt(camera_distance * camera_distance - camera_z * camera_z);

	}
	else if (camera_z <= camera_distance + 1 && camera_z >= 0 && !I)
	{

		camera_z -= speed;
		camera_x = -sqrt(camera_distance * camera_distance - camera_z * camera_z);

	}
}

void shiftCameraSmoothly(double x, double z)
{
	if (camera_x != x || camera_z != z){
		RotateCamera(0.5);
		gluLookAt(camera_x, 20, camera_z,
			0, 0, 0,
			0, 1, 0);
	}
	else
	{

		gluLookAt(x, 20, z,
			0, 0, 0,
			0, 1, 0);
	}
}

printingInfos() {
	if (info)
	{
		printInfo("X : %.2f", -40, 22, ball.location[0]);
		printInfo("Y : %.2f", -40.2, 21, ball.location[1]);
		printInfo("Z : %.2f", -40.4, 20, ball.location[2]);

		printInfo("Vx : %.2f", -40.8, 18, ball.velocity[0]);
		printInfo("Vy : %.2f", -41, 17, ball.velocity[1]);
		printInfo("Vz : %.2f", -41.2, 16, ball.velocity[2]);

		printInfo("Wx : %.2f", -41.6, 14, ball.rotation[1]);
		printInfo("Wy : %.2f", -41.8, 13, ball.rotation[0]);

		printInfo("ball mass : %.0f", 30, 22, ball.mass);
		printInfo("racket mass : %.0f", 30.2, 21, racket.mass);
		printInfo("gravity : %.2f", 30.4, 20, gravity);
		printInfo("air density : %.2f", 30.6, 19, p);
	}
}