#pragma once

#include "cScene.h"
#include "cData.h"
#include "cPlayer.h"
#include "cPhysics.h"
#include "cCamera.h"


#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void ReadDraggedMouse(int x, int y);
	//Process
	bool Process();
	//Output
	void Render();
	void BallPhysics();
	void BlockPhysics();

private:
	unsigned char keys[256];
	float cam_x, cam_y, cam_z;
	float azimut, fita;
	cScene Scene;
	cData Data;
	cPlayer Player;
	cPhysics Physics;
	cCamera Camera;
};
