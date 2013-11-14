#include "cBlock.h"
#include "Globals.h"


cBlock::cBlock(void) 
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}
cBlock::~cBlock(void){}

void cBlock::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void cBlock::Draw()
{

	float x_left, x_right, y_up, y_down, z_near, z_far;

	x_left = x - BLOCK_WIDTH / 2.0;
	x_right = x + BLOCK_WIDTH / 2.0;

	y_up = y + BLOCK_HEIGHT / 2.0;
	y_down = y - BLOCK_HEIGHT / 2.0;

	z_near = z + BLOCK_DEPTH / 2.0;
	z_far = z - BLOCK_DEPTH / 2.0;
	
	glBegin(GL_QUADS);

	glColor3f(1.0, 0.0, 0.0);
	// Front Face
	glVertex3f(x_left, y_down, z_far);
	glVertex3f(x_right, y_down, z_far);
	glVertex3f(x_right, y_up, z_far);
	glVertex3f(x_left, y_up, z_far);
	// Back Face
	glVertex3f(x_left, y_down, z_near);
	glVertex3f(x_right, y_down, z_near);
	glVertex3f(x_right, y_up, z_near);
	glVertex3f(x_left, y_up, z_near);
	// Right face
	glVertex3f(x_right, y_down, z_far);
	glVertex3f(x_right, y_up, z_far);
	glVertex3f(x_right, y_up, z_near);
	glVertex3f(x_right, y_down, z_near);
	// Left Face
	glVertex3f(x_left, y_down, z_far);
	glVertex3f(x_left, y_down, z_near);
	glVertex3f(x_left, y_up, z_near);
	glVertex3f(x_left, y_up, z_far);

	// Top Face
	glVertex3f(x_left, y_up, z_near);
	glVertex3f(x_right, y_up, z_near);
	glVertex3f(x_right, y_up, z_far);
	glVertex3f(x_left, y_up, z_far);

	// Bottom Face
	glVertex3f(x_left, y_down, z_near);
	glVertex3f(x_right, y_down, z_near);
	glVertex3f(x_right, y_down, z_far);
	glVertex3f(x_left, y_down, z_far);

	glColor3f(1.0, 1.0, 1.0);

	glEnd();

}