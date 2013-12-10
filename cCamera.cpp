#include "cCamera.h"
#include "Globals.h"

cCamera::cCamera(void) {
	diagonalEscena = sqrt((float)(32 * 16 * 3));
	R = diagonalEscena;
}
cCamera::~cCamera(void){}

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

void cCamera::Draw()
{
	float Vx, Vy, Vz;
	float angFITA = fita*M_PI / 180; //pasas los grados a radianes, para que luego 
	float angAZIM = azimut*M_PI / 180; //al hacer sen y cos nos lo de directamente en grados,
	Vx = cos(angFITA)*sin(angAZIM);
	Vy = sin(angFITA);
	Vz = cos(angFITA)*cos(angAZIM);
	//glLoadIdentity();
	gluLookAt(Vx*R, Vy*R, Vz*R, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}