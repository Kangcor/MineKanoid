#include "Globals.h"

#define frand()			((float)rand()/RAND_MAX)

class cParticle
{
public:
	cParticle(void);
	void iniParticles(float x, float y, float z);
	void Draw();

private:
	typedef struct {
		float	life;		// vida
		float	fade;		// fade
		float	r, g, b;    // color
		GLfloat x, y, z;    // posicion
		GLfloat vx, vy, vz; // velocidad 
		GLfloat ax, ay, az; // aceleracion
	} Particle;

	Particle particula[50];
};
