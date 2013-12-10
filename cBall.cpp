#include "cBall.h"
#include "Globals.h"


cBall::cBall(void) 
{
	this->x = 0.0;
	this->y = -(SCENE_HEIGHT/2) + BALL_RADIUS;
	this->z = 0.0;
	this->difX = 0.1;
	this->difZ = 0.1;
	this->r = 0;
	this->g = 0;
	this->b = 255;
}
cBall::~cBall(void){}

void cBall::setPos(float x, float z)
{
	this->x = x;
	this->z = z;
}

float cBall::getX()
{
	return x;
}

float cBall::getZ()
{
	return z;
}

void cBall::setColor(float r, float g, float b)
{
        this->r = r;
        this->g = g;
        this->b = b;
}

void cBall::Draw()
{
	glPushMatrix();
	glColor3f(r, g, b);
	glTranslatef(x, y, z);
	glutWireSphere(BALL_RADIUS, 10, 10);
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();	
}

void cBall::Logic(float position)
{
	x += difX;
	z += difZ;

	if (z >= SCENE_DEPTH/2 && z <= (SCENE_DEPTH/2)+1) {
		if (x >= position && x <= position+PLAYER_WIDTH/2) {
			difZ *= -1;
		}
		else if (x <= position && x >= position-PLAYER_WIDTH/2) {
			difZ *= -1;
		}
	}

	if(x > SCENE_WIDTH/2) difX *= -1;
	if(x < -SCENE_WIDTH/2) difX *= -1;
	if(z < -SCENE_DEPTH/2) difZ *= -1;
	if(z > (SCENE_DEPTH/2)+2) {
		setPos(0,12);
		difX = 0.1;
		difZ = 0.1;
	}
}