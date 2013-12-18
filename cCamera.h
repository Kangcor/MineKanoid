#pragma once

#include "cData.h"
#define _USE_MATH_DEFINES
#include <math.h>

class cCamera
{
public:
	cCamera(void);
	virtual ~cCamera(void);
	void setAzimut(float azimut);
	float getAzimut();
	void setRadius(float R);
	float getRadius();
	void ReadMouse(int button, int state, int x, int y);
	void ReadDraggedMouse(int x, int y);

	void nextLevel(int level);

	void Draw();

private:
	float diagonalEscena;
	int R;
	float Vx, Vz, Ex, Ez;
	double obsx, obsy, obsz, vrpx, vrpy, vrpz, upx, upy, upz;
	float azimut, fita;
	int prex, prey;
	bool left, right, away, approach;
	int level;
};
