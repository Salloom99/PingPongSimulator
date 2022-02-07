#include "Collision.h"

int didCollide(	obj *sphere,const float location[3],const float dimentions[3])
{
	float point1[3];
	float point2[3];

	int p = 1; // assuming that the ball did collide

	for (int i = 0; i < 3; i++)
	{
		point1[i] = location[i] - (dimentions[i] * 0.5);
		point2[i] = location[i] + (dimentions[i] * 0.5);

		if (!(point1[i] <= sphere->location[i] + sphere->radius) ||
			!(sphere->location[i] - sphere->radius <= point2[i]))
			p *= 0; // if one of the conditions did not occur then there's no collision
	}

	return p;
}

int collision(obj *temp, obj* temp2)
{
	
	if(didCollide(temp, temp2->location, temp2->bounds))
	{
		int y = -1;

	
		// the ball looses some of its rotation energy when colliding
		temp->rotation[0] = temp->rotation[0] * 0.5;
		temp->rotation[1] = temp->rotation[1] * 0.5;
		
		

		
		for (int i = 0; i < 3; i++)
		{
			temp->location[i] = temp->oldLocation[i];
			temp2->location[i] = temp2->oldLocation[i];

			float ballOldVelocity = temp->velocity[i];

			temp->velocity[i] = -0.5 * temp->velocity[i];
			temp->velocity[i] += 0.5 * temp2->velocity[i] * temp2->mass / temp->mass;

			// transistional energy to rotational enrgy
			if(i == 1)
				temp->rotation[1] -= temp2->velocity[1] * M_PI / 4;
			if (i == 0)
				temp->rotation[0] -= temp2->velocity[0] * M_PI / 3;

			temp2->velocity[i] = 0.2 * ballOldVelocity * temp->mass / temp2->mass;
		}

		// and thats some of rotational energy converted to transitional energy
		temp->velocity[0] += temp->rotation[0];

		return 1;
	}
	return 0;
}


int collision2(obj* temp,rect3D rect)
{

	if (didCollide(temp, rect.center, rect.dimentions))
	{
		int y = -1;

		// the ball looses some of its rotation energy when colliding
		temp->rotation[0] *= 0.5;
		temp->rotation[1] *= 0.5;

		// and thats some of rotational energy converted to transitional energy
		temp->velocity[2] += temp->rotation[1] * ball.radius;

		for (int i = 0; i < 3; i++)
		{
			temp->location[i] = temp->oldLocation[i];

			if (!didCollide(temp, rect.center, rect.dimentions) && y == -1)
				y = i;
		}
		temp->velocity[y] = -rect.reboundFactor* temp->velocity[y];
		return 1;
	}
	return 0;
}


void collisionDetection()
{
	if (collision2(&ball, table))
	{
		ball.velocity[2] += ball.rotation[1] * ball.radius;
	}
	if(collision2(&ball, net))
		printf("Net !!\n");

	
	if(collision(&ball, &racket))
	{
		
	}
	return;
}
void ballBounds() 
{

	// if the ball hits the boundries
	if (ball.location[2] <= -50 + ball.radius ||
		ball.location[2] >= 50 - ball.radius)
		ball.velocity[2] = -0.6 * ball.velocity[2];
	if (ball.location[1] <= -10 + ball.radius ||
		ball.location[1] >= 30 - ball.radius)
		ball.velocity[1] = -0.6 * ball.velocity[1];
	if (ball.location[0] >= 50 - ball.radius ||
		ball.location[0] <= -50 + ball.radius)
		ball.velocity[0] = -0.6 * ball.velocity[0];

}
void racketBounds(float x1,float x2,float z1,float z2)
{

	if (racket.location[0] <= x1) //x1
	{
		racket.velocity[0] = 0;
		racket.location[0] = x1;
	}
	else if (racket.location[0] >= x2) //x2
	{
		racket.velocity[0] = 0;
		racket.location[0] = x2;
	}
	
	if (racket.location[2] <= z1) //z1
	{
		racket.velocity[2] = 0;
		racket.location[2] = z1;
	}
	else if (racket.location[2] >= z2) //z2
	{
		racket.velocity[2] = 0;
		racket.location[2] = z2;
	}

	if (racket.location[1] <= 2.0) //y1
	{
		racket.velocity[1] = 0;
		racket.location[1] = 2;
	}
	else if (racket.location[1] >= 10.0) //y2
	{
		racket.velocity[1] = 0;
		racket.location[1] = 9.9;
	}
	return;
}