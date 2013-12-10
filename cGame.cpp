#include "cGame.h"
#include "Globals.h"
#define _USE_MATH_DEFINES
#include <math.h>


cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	bool res=true;

	azimut = 1;
	fita = 1;
	cam_x = cam_y = cam_z = 1.0;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_WALL,"wall.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FLOOR,"floor.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ROOF,"roof.png",GL_RGBA);
	if(!res) return false;

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
	Scene.RenderBlocks();
	Scene.RenderBalls(Player.getPosition());
	Player.Draw(&Data);

	glutSwapBuffers();
}

void cGame::BallPhysics() {
	std::vector<cBall> balls = Scene.GetBalls();
	for(int i = 0; i < 10; ++i) {
		if (Physics.Collide(balls[i], Player)) balls[i].setColor(255, 0, 0);
	}
	Scene.SetBalls(balls);
}
