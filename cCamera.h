#pragma once

#include "cData.h"
#define _USE_MATH_DEFINES
#include <math.h>

class cCamera
{
public:
	cCamera(void);
	virtual ~cCamera(void);

	void ReadMouse(int button, int state, int x, int y);
	void ReadDraggedMouse(int x, int y);
	void Draw();

private:
	float diagonalEscena;
	int R;
	double obsx, obsy, obsz, vrpx, vrpy, vrpz, upx, upy, upz;
	float azimut, fita;
	int prex, prey;
};
