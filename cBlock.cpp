#include "cBlock.h"
#include "Globals.h"
#include <cstdlib>

cBlock::cBlock(void) 
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	pinta = true;
	cayendo = false;
	
}
cBlock::~cBlock(void){}

void cBlock::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	particula.iniParticles(x, y, z);
}

void cBlock::setTex(int tex)
{
	this->tex = tex;
}

float cBlock::getX()
{
	return this->x;
}

float cBlock::getY()
{
	return this->x;
}

float cBlock::getZ()
{
	return this->z;
}

void cBlock::setColor(float r, float g, float b)
{
        this->r = r;
        this->g = g;
        this->b = b;
}

void cBlock::DrawParticle()
{
	particula.Draw();
}

void cBlock::Draw(cData *Data)
{
	if (pinta) 
	{
		float x_left, x_right, y_up, y_down, z_near, z_far;

		x_left = x - BLOCK_WIDTH / 2.0;
		x_right = x + BLOCK_WIDTH / 2.0;

		y_up = y + BLOCK_HEIGHT / 2.0;
		y_down = y - BLOCK_HEIGHT / 2.0;

		z_near = z + BLOCK_DEPTH / 2.0;
		z_far = z - BLOCK_DEPTH / 2.0;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, Data->GetID(this->tex));
		glBegin(GL_QUADS);

		//glColor3f(r, g, b);
		// Front Face
		glTexCoord2f(1, 1); glVertex3f(x_right, y_down, z_far);
		glTexCoord2f(1, 0.0f); glVertex3f(x_right, y_up, z_far);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x_left, y_up, z_far);
		glTexCoord2f(0.0f, 1); glVertex3f(x_left, y_down, z_far);
		glEnd();

		if (this->tex == IMG_PUMPKIN) glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_PUMPKIN_FACE));
		else glBindTexture(GL_TEXTURE_2D, Data->GetID(this->tex));
		// Back Face
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1); glVertex3f(x_right, y_down, z_near);
		glTexCoord2f(1, 0.0f); glVertex3f(x_right, y_up, z_near);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x_left, y_up, z_near);
		glTexCoord2f(0.0f, 1);  glVertex3f(x_left, y_down, z_near);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, Data->GetID(this->tex));
		glBegin(GL_QUADS);
		// Right face
		glTexCoord2f(0.0f, 1); glVertex3f(x_right, y_down, z_far);
		glTexCoord2f(1, 1); glVertex3f(x_right, y_down, z_near);
		glTexCoord2f(1, 0.0f); glVertex3f(x_right, y_up, z_near);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x_right, y_up, z_far);
		// Left Face
		glTexCoord2f(0.0f, 1); glVertex3f(x_left, y_down, z_far);
		glTexCoord2f(1, 1); glVertex3f(x_left, y_down, z_near);
		glTexCoord2f(1, 0.0f); glVertex3f(x_left, y_up, z_near);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x_left, y_up, z_far);

		glEnd();

		if (this->tex == IMG_GRASS_SIDE)
		{
			glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_GRASS_TOP));
		}
		else if (this->tex == IMG_PUMPKIN)
		{
			glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_PUMPKIN_TOP));
		}
		else if (this->tex == IMG_TNT_SIDE)
		{
			glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_TNT_TOP));
		}

		glBegin(GL_QUADS);
		// Top Face
		glTexCoord2f(1, 1); glVertex3f(x_left, y_up, z_near);
		glTexCoord2f(1, 0.0f); glVertex3f(x_right, y_up, z_near);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x_right, y_up, z_far);
		glTexCoord2f(0.0f, 1); glVertex3f(x_left, y_up, z_far);

		// Bottom Face
		glVertex3f(x_left, y_down, z_near);
		glVertex3f(x_right, y_down, z_near);
		glVertex3f(x_right, y_down, z_far);
		glVertex3f(x_left, y_down, z_far);

		glEnd();
	}
}