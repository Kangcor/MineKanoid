#include "cGame.h"
#include "Globals.h"
#define _USE_MATH_DEFINES
#include <math.h>


cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	bool res=true;

	//Scene initialization
	res = Data.LoadImage(IMG_BRICK, "brick.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PUMPKIN, "pumpkin_side.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_IRON, "iron_block.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_STONE, "stone.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_GRASS_SIDE, "grass_side.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_GRASS_TOP, "wool_colored_lime.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PUMPKIN_TOP, "pumpkin_top.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PUMPKIN_FACE, "pumpkin_face_off.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_TNT_SIDE, "tnt_side.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_TNT_TOP, "tnt_top.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_WALL, "wall.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_FLOOR, "floor.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_ROOF, "roof.png", GL_RGBA);
	if (!res) return false;
	//manager.InitShaders(&Data);

	azimut = 1;
	fita = 1;
	cam_x = cam_y = cam_z = 1.0;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Luz ambiente
	float ambiente[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);

	//Luz difusa
	float difusa[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);

	//Luz especular
	float especular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular);

	float position[] = { 0, -50, 0, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	Scene.Init();
	return res;
}

bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
	Camera.ReadMouse(button, state, x, y);
}

void cGame::ReadDraggedMouse(int x, int y) {
	Camera.ReadDraggedMouse(x, y);
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	if (keys[GLUT_KEY_RIGHT]) Player.setPosition(Player.getPosition() + 0.2);
	if (keys[GLUT_KEY_LEFT]) Player.setPosition(Player.getPosition() - 0.2);
	//Game Logic
	//...

	BallPhysics();
	BlockPhysics();
	return res;
}

//Output
void cGame::Render()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	
	Camera.Draw();

//	glTranslatef(0.0f,-2.0f,-50.0f);
//	glRotatef(20,1.0f,0.0f,0.0f);

	Scene.Draw(&Data);
	Scene.RenderBlocks(&Data);
	Scene.RenderBalls();
	Player.Draw(&Data);

	glutSwapBuffers();
}

void cGame::BallPhysics() {
	std::vector<cBall> balls = Scene.GetBalls();
	for(int i = 0; i < 1; ++i) {
		Physics.CollidePlayer(balls[i], Player);
	}
	Scene.SetBalls(balls);
}

void cGame::BlockPhysics() {
	std::vector<cBlock> blocks = Scene.GetBlocks();
	std::vector<cBall> balls = Scene.GetBalls();
	for(int i = 0; i < NUM_ROWS*NUM_COLUMNS; ++i) {
		if (blocks[i].pinta) Physics.CollideBlock(balls[0], blocks[i]);
	}
	Scene.SetBlocks(blocks);
	Scene.SetBalls(balls);
}
