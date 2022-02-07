#include "Objects.h"
#include <math.h>

void drawNet()
{
	
	glColor3f(0.86, 0.86, 0.86);

	// left 
	glBegin(GL_POLYGON);
		glVertex3f(-15,2.3,0);
		glVertex3f(-15,0,0);
		glVertex3f(-15.3,0,0);
		glVertex3f(-15.3,2.3,0);	
	glEnd();

	// right
	glBegin(GL_POLYGON);
		glVertex3f(15,2.3,0);
		glVertex3f(15,0,0);
		glVertex3f(15.3,0,0);
		glVertex3f(15.3,2.3,0);	
	glEnd();

	// top
	glBegin(GL_POLYGON);
		glVertex3f(-15.3,2,0);
		glVertex3f(-15.3,2.3,0);
		glVertex3f(15.3,2.3,0);
		glVertex3f(15.3,2,0);		
	glEnd();


	// bottom
	glBegin(GL_POLYGON);
		glVertex3f(-15, 0, 0);
		glVertex3f(-15, 0.3, 0);
		glVertex3f(15, 0.3, 0);
		glVertex3f(15, 0, 0);
	glEnd();


	/// ---------------------<Grid>
	float test = 2;
	for(int y=1; y <= 6; y++) 
	{
		glPushMatrix();
			for(int x=0; x <= 73; x++)
			{

				glTranslated(0.4,test,0);
				glBegin(GL_POLYGON); 
					glColor3f(0.49,0.49,0.49);
					glVertex3f(-15,0.1,0);
					glVertex3f(-15,0.2,0);
					glVertex3f(-15.2,0.2,0);
					glVertex3f(-15.2,0.1,0);
				glEnd();
				test = 0;
			}
		glPopMatrix();
		test = 0.4*(float)y;
	}
	/// ---------------------</Grid>


	/// ---------------------<Grib>
	glBegin(GL_POLYGON);
		glColor3f(0.16, 0.16, 0.16);
		glVertex3f(-15.3, 0, 0);
		glVertex3f(-13, 0, 0);
		glVertex3f(-13, -1.5, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.16, 0.16, 0.16);
		glVertex3f(15.3, 0, 0);
		glVertex3f(13, 0, 0);
		glVertex3f(13, -1.5, 0);
	glEnd();

	/// ---------------------</Grib>
}

void drawTable()
{
	//Table
 	glBegin(GL_POLYGON); 
		glColor3f(0.32, 0.44, 0.32);
		glVertex3f(-13,	0,	-26);
		glVertex3f(-13,	0,	26);
		glVertex3f(13,	0,	26);
		glVertex3f(13,	0,	-26);
	glEnd();

	/// --------------------------<WhiteLines>

	// GL_LINE_WIDTH
	glLineWidth((GLfloat)5);
 	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-13, 0.05, -26);
		glVertex3f(-13, 0.05, 26);
		glVertex3f(13, 0.05, 26);
		glVertex3f(13, 0.05, -26);
	glEnd();

	glLineWidth((GLfloat)1);
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0, 0.05, -26);
		glVertex3f(0, 0.05, 26);
	glEnd();


	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-13, 0.05, 0);
		glVertex3f(13, 0.05, 0);
	glEnd();
	

	/// --------------------------</WhiteLines>


	/// --------------------------<Thickness>

	// front
	glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex3f(-13, 0, 26);
		glVertex3f(13, 0, 26);
		glVertex3f(13, -0.7, 26);
		glVertex3f(-13, -0.7, 26);
	glEnd();

	// back
	glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex3f(-13, 0, -26);
		glVertex3f(13, 0, -26);
		glVertex3f(13, -0.7, -26);
		glVertex3f(-13, -0.7, -26);
	glEnd();

	// right
	glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex3f(13, 0, -26);
		glVertex3f(13, 0, 26);
		glVertex3f(13, -0.7, 26);
		glVertex3f(13, -0.7, -26);
	glEnd();

	// left
	glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex3f(-13, 0, -26);
		glVertex3f(-13, 0, 26);
		glVertex3f(-13, -0.7, 26);
		glVertex3f(-13, -0.7, -26);
	glEnd();
	/// --------------------------</Thickness>

	// legs
	drawTableLegs();

	// net
	drawNet();
}

void drawRacket(float x, float y, float z)
{
	static GLMmodel* pmodel = NULL;

	glPushMatrix();
	//glRotatef(180,x, 1, z);
	glTranslated(x,y,z);
	//glColor3f(RGB(0xFF), RGB(0xFF), RGB(255));
    if (!pmodel) {
        pmodel = glmReadOBJ("racket3.obj");
        if (!pmodel) exit(0);
		glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
		glmScale(pmodel,2);
	}
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

void drawBall()
{
	glPushMatrix();
		glTranslated(ball.location[0], ball.location[1], ball.location[2]);
		glColor3f(1, 0.64, 0);
		glutSolidSphere(ball.radius,30,30);
	glPopMatrix();
}

void drawBallShadow()
{
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		drawCircle(ball.location[0], 0, ball.location[2], powf(ball.location[1],0.3)*0.3, 30);
	glPopMatrix();
}

void drawRacketShadow()
{
	glPushMatrix();
	glTranslated(racket.location[0], 0.2, racket.location[2]);
	for(int i = 0; i < 4; i++)
	{
		glRotated(180.0, 0.0, 1.0, 0.0);
 		glBegin(GL_POLYGON); 
				glColor3f(0.0,		0.0,		0.0);
			glVertex3f(0,		0.0,		0.0);
			glVertex3f(0,		0.0,		0.5);
			glVertex3f(0.5,		0.0,		0.5);
			glVertex3f(2.0,		0.0,		0.0);
		glEnd();


 		glBegin(GL_POLYGON); 
				glColor3f(0.0,		0.0,		0.0);
			glVertex3f(0,		0.0,		0.0);
			glVertex3f(0,		0.0,		0.5);
			glVertex3f(-0.5,		0.0,		0.5);
			glVertex3f(-2.0,		0.0,		0.0);
		glEnd();
		
	}
	glPopMatrix();
}

void drawLeg(int leg_x,int leg_z) {
	float width = 2;
	float depth = 2;

	// front
	glBegin(GL_POLYGON);
	glColor3f(0.16, 0.16, 0.16);
	glVertex3f(leg_x - width / 2, -0.1, leg_z + depth / 2);
	glVertex3f(leg_x + width / 2, -0.1, leg_z + depth / 2);
	glVertex3f(leg_x + width / 2, -10, leg_z + depth / 2);
	glVertex3f(leg_x - width / 2, -10, leg_z + depth / 2);
	glEnd();

	// right
	glBegin(GL_POLYGON);
	glColor3f(0.16, 0.16, 0.16);
	glVertex3f(leg_x - width / 2, -0.1, leg_z - depth / 2);
	glVertex3f(leg_x - width / 2, -0.1, leg_z + depth / 2);
	glVertex3f(leg_x - width / 2, -10, leg_z + depth / 2);
	glVertex3f(leg_x - width / 2, -10, leg_z - depth / 2);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glColor3f(0.16, 0.16, 0.16);
	glVertex3f(leg_x + width / 2, -0.1, leg_z - depth / 2);
	glVertex3f(leg_x + width / 2, -0.1, leg_z + depth / 2);
	glVertex3f(leg_x + width / 2, -10, leg_z + depth / 2);
	glVertex3f(leg_x + width / 2, -10, leg_z - depth / 2);
	glEnd();

	// back
	glBegin(GL_POLYGON);
	glColor3f(0.16, 0.16, 0.16);
	glVertex3f(leg_x - width / 2, -0.1, leg_z - depth / 2);
	glVertex3f(leg_x + width / 2, -0.1, leg_z - depth / 2);
	glVertex3f(leg_x + width / 2, -10, leg_z - depth / 2);
	glVertex3f(leg_x - width / 2, -10, leg_z - depth / 2);
	glEnd();
}

void drawTableLegs() {

	// Front Right Leg
	drawLeg(10, 20);
	
	// Front Left Leg
	drawLeg(-10, 20);

	// Back Right Leg
	drawLeg(10, -20);

	// Back Left Leg
	drawLeg(-10, -20);

	// table shadow
	glBegin(GL_POLYGON);
		glColor3f(0.13, 0.15, 0.4);
		glVertex3f(-13, -9.91, -26);
		glVertex3f(-13, -9.91, 26);
		glVertex3f(13, -9.91, 26);
		glVertex3f(13, -9.91, -26);
	glEnd();
}

void drawShadows()
{
	if(racket.location[0] >=-13 && racket.location[0] <= 13 && racket.location[2] > -25 && racket.location[2] < 25)
		drawRacketShadow();
	if (ball.location[0] > -12 && ball.location[0] < 12 && ball.location[2] > -25 && ball.location[2] < 25)
		drawBallShadow();
}

void drawRoom()
{
	glPushMatrix();
		// bottom
 		glBegin(GL_POLYGON); 
			glColor3f(0.2, 0.3, 0.6);
			glVertex3f(-50,	-10,	-50);
			glVertex3f(-50,	-10,	50);
			glVertex3f(50,	-10,	50);
			glVertex3f(50,	-10,	-50);
		glEnd();
		// left
		glBegin(GL_POLYGON);
			glColor3f(0.5, 0.5, 0.5);
			glVertex3f(-50, -10, -50);
			glVertex3f(-50, -10, 50);
			glVertex3f(-50, 30, 50);
			glVertex3f(-50, 30, -50);
		glEnd();
		// right
		glBegin(GL_POLYGON);
			glColor3f(0.5, 0.5, 0.5);
			glVertex3f(50, -10, -50);
			glVertex3f(50, -10, 50);
			glVertex3f(50, 30, 50);
			glVertex3f(50, 30, -50);
		glEnd();
		// front
		glBegin(GL_POLYGON);
			glColor3f(0.5, 0.5, 0.5);
			glVertex3f(-50, -10, -49);
			glVertex3f(-50, -10, -49);
			glVertex3f(50, 30, -49);
			glVertex3f(50, 30, -49);
		glEnd();
	glPopMatrix();
}

void drawCircle(float cx, float cy, float cz,float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * i / num_segments;
		float x = r * cosf(theta);
		float z = r * sinf(theta);

		glVertex3f(x + cx, 0, z + cz);

	}
	glEnd();
}
