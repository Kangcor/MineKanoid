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
	int scene;
	bool move, away, left, right;
	cScene Scene1;
	cScene Scene2;
	cScene Scene3;
	cScene Scene4;
	cData Data;
	cPlayer Player1;
	cPlayer Player2;
	cPlayer Player3;
	cPlayer Player4;
	cPhysics Physics;
	cCamera Camera;
	int frame;
};
