#include "cParticle.h"
#define _USE_MATH_DEFINES
#include <math.h>

cParticle::cParticle()
{

}

void cParticle::iniParticles(float x, float y, float z)
{
	GLfloat v, theta, phi;
	int i;

	for (i = 0; i < 50; i++)
	{
		v = 0.1*frand() + 0.2;
		phi = frand()*M_PI;
		theta = 2.0*frand()*M_PI;
		particula[i].x = x;
		particula[i].y = y;
		particula[i].z = z;
		particula[i].vx = v * cos(theta) * sin(phi);
		particula[i].vy = v * cos(phi);
		particula[i].vz = v * sin(theta) * sin(phi);
		particula[i].ax = ((rand()%3) - 1)*0.01;
		particula[i].ay = 0.00f;
		particula[i].az = 0.0f;
		particula[i].r = 0.882f;
		particula[i].g = 0.552f;
		particula[i].b = 0.211f;
		particula[i].life = 0.5f;
		particula[i].fade = 0.01f;
	}
}

void cParticle::Draw()
{
	for (int i = 0; i < 50; i++)
	{
		glColor4f(particula[i].r, particula[i].g, particula[i].b, particula[i].life);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(1, 1); glVertex3f(particula[i].x + 0.2f, particula[i].y + 0.2f, particula[i].z);
		glTexCoord2d(0, 1); glVertex3f(particula[i].x - 0.2f, particula[i].y + 0.2f, particula[i].z);
		glTexCoord2d(1, 0); glVertex3f(particula[i].x + 0.2f, particula[i].y - 0.2f, particula[i].z);
		glTexCoord2d(0, 0); glVertex3f(particula[i].x - 0.2f, particula[i].y - 0.2f, particula[i].z);
		glEnd();
		particula[i].x += particula[i].vx;
		particula[i].y += particula[i].vy;
		particula[i].z += particula[i].vz;
		particula[i].vx += particula[i].ax;
		particula[i].vy += particula[i].ay;
		particula[i].vz += particula[i].az;
		particula[i].life -= particula[i].fade;
	}
}