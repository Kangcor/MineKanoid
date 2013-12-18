#include "cCamera.h"
#include "Globals.h"

cCamera::cCamera(void) {
	diagonalEscena = sqrt((float)(32 * 16 * 3));
	R = 2;
	fita = 30;
	Ex = 0;
	Ez = 0;
	left = false;
	right = false;
	away = false;
	approach = false;
	level = 0;
}
cCamera::~cCamera(void){}

void cCamera::setAzimut(float azimut)
{
	this->azimut = azimut;
}

float cCamera::getAzimut()
{
	return azimut;
}

void cCamera::setRadius(float R)
{
	this->R = R;
}

float cCamera::getRadius()
{
	return R;
}

void cCamera::ReadMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			prex = x;
			prey = y;
		}
	}
}

void cCamera::ReadDraggedMouse(int x, int y)
{
	float incrX = prex - x;
	float incrY = prey - y;

	incrX /= 2;
	incrY /= 2;
	fita += incrY;

	while (fita > 89) fita = 89;
	while (fita<-89) fita = -89;

	azimut += incrX;
	if (azimut > 360) azimut -= 360;
	else if (azimut < 0) azimut += 360;
	prex = x;
	prey = y;
}

void cCamera::nextLevel(int level)
{
	if (level < this->level)
	{
		left = true;
	}
	else
	{
		right = true;
	}
	this->level = level;
	away = true;
}

void cCamera::Draw()
{
	
	/*float angFITA = fita*M_PI / 180; //pasas los grados a radianes, para que luego 
	float angAZIM = azimut*M_PI / 180; //al hacer sen y cos nos lo de directamente en grados,
	Vx = cos(angFITA)*sin(angAZIM);
	//Vy = sin(angFITA);
	Vz = cos(angFITA)*cos(angAZIM);
	//glLoadIdentity();*/

	if (away)
	{
		if (this->R > 2) this->R -= 1;
		else
		{
			if (right)
			{
				if (this->level == 1)
				{
					if (Ex < SCENE_WIDTH * 2) Ex += 1;
					else
					{
						right = false;
						away = false;
						approach = true;
					}
				}
				else if (this->level == 2)
				{
					if (Ex < SCENE_WIDTH * 4) Ex += 1;
					else
					{
						right = false;
						away = false;
						approach = true;
					}
				}
			}

			if (left)
			{
				if (this->level == 1)
				{
					if (Ex > SCENE_WIDTH * 2) Ex -= 1;
					else
					{
						left = false;
						away = false;
						approach = true;
					}
				}
				else if (this->level == 0)
				{
					if (Ex > 0) Ex -= 1;
					else
					{
						left = false;
						away = false;
						approach = true;
					}
				}
			}
		}
	}

	if (approach)
	{
		if (this->R < tan(22.5)*(SCENE_WIDTH / 2.0)) this->R += 1;
		else approach = false;
	}

	gluLookAt(Ex, 10, -R, Ex, 0, -SCENE_WIDTH*2, 0.0, 1.0, 0.0);
	
}