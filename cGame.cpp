#include "cGame.h"
#include "Globals.h"
#define _USE_MATH_DEFINES
#include <math.h>


cGame::cGame(void) 
{
	frame = 0;
}
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
	res = Data.LoadImage(IMG_WOOD, "planks_spruce.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_ROOF, "cobblestone_mossy.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_GOLD, "gold_block.png", GL_RGBA);
	if (!res) return false;

	//manager.InitShaders(&Data);
	scene = 0;
	move = false;
	away = false;
	left = false;
	right = false;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	//Luz ambiente
	float ambiente[] = { 1, 1, 1, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambiente);

	//Luz difusa
	float difusa[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, difusa);

	//Luz especular
	float especular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
	glLightfv(GL_LIGHT1, GL_SPECULAR, especular);
	glLightfv(GL_LIGHT2, GL_SPECULAR, especular);

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCENE_WIDTH, SCENE_WIDTH);
	float rAspecto = (float)(SCENE_WIDTH + 2) / (float)SCENE_DEPTH;
	double asp = (double)rAspecto;
	int left, right, top, bottom;
	if (rAspecto < 1 && (SCENE_WIDTH + 2) / 2 < 50){
		left = -(SCENE_WIDTH + 2) / 2;
		right = (SCENE_WIDTH + 2) / 2;
		bottom = -50;
		top = 50;
	}
	else if (rAspecto > 1 && SCENE_DEPTH / 2 < 50){
		left = -50;
		right = 50;
		bottom = -SCENE_DEPTH / 2;
		top = SCENE_DEPTH / 2;
	}
	else{
		left = -50;
		right = 50;
		bottom = -50;
		top = 50;
	}

	//Camera.setAzimut(90);

	gluPerspective(45.0, asp, 0.1, 1000.0);
	//gluPerspective(45.0,(float)(SCREEN_WIDTH)/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	Scene1.Init(0);
	Scene2.Init(1);
	Scene3.Init(2);
	
	move = true;

	return res;
}

bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();
	frame++;

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
	if (keys[GLUT_KEY_RIGHT]) Player1.setPosition(Player1.getPosition() + 0.2);
	if (keys[GLUT_KEY_LEFT]) Player1.setPosition(Player1.getPosition() - 0.2);
	if (keys[108])
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}
	if (keys[109])
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
	if (keys[119])
	{
		move = true;
		keys[97] = false;
	}
	if (keys[115])
	{
		away = true;
		keys[102] = false;
	}
	if (keys[97])
	{
		left = true;
		Camera.nextLevel(0);
		keys[97] = false;
	}
	if (keys[100])
	{
		right = true;
		Camera.nextLevel(1);
		keys[100] = false;
	}

	//Game Logic
	//...

	BallPhysics();
	if (frame > 10)
	{
		BlockPhysics();
		frame = 0;
	}
	return res;
}

//Output
void cGame::Render()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	
	Camera.Draw();

	glPushMatrix();
	glTranslatef(0, 0, -SCENE_WIDTH*2 - 1);
	glRotatef(15, 1, 0, 0);
	float position1[] = { 0, 50, -SCENE_WIDTH*2, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position1);
	Scene1.Draw(&Data);
	Scene1.RenderBlocks(&Data);
	Scene1.RenderBalls();
	Player1.Draw(&Data);
	Scene1.RenderWin(&Data);
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(SCENE_WIDTH * 2, 0, -SCENE_WIDTH * 2 - 1);
	glRotatef(15, 1, 0, 0);
	float position2[] = { SCENE_WIDTH*2, 50, 0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	Scene2.Draw(&Data);
	Scene2.RenderBlocks(&Data);
	Scene2.RenderBalls();
	Player2.Draw(&Data);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(SCENE_WIDTH*4, 0, -SCENE_WIDTH*2 -1);
	glRotatef(15, 1, 0, 0);
	float position3[] = { -SCENE_WIDTH*2, 50, 0, 1.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, position3);
	Scene3.Draw(&Data);
	Scene3.RenderBlocks(&Data);
	Scene3.RenderBalls();
	Player3.Draw(&Data);
	glPopMatrix();

	glutSwapBuffers();
}

void cGame::BallPhysics() {
	std::vector<cBall> balls = Scene1.GetBalls();
	for(int i = 0; i < 1; ++i) {
		Physics.CollidePlayer(balls[i], Player1);
	}
	Scene1.SetBalls(balls);
}

void cGame::BlockPhysics() {
	std::vector<std::vector <cBlock> > blocks = Scene1.GetBlocks();
	std::vector<cBall> balls = Scene1.GetBalls();
	for (int i = 0; i < NUM_ROWS*NUM_COLUMNS; ++i) {
		if (blocks[i][0].pinta) Physics.CollideBlock(balls[0], blocks[i][0]);
	}
	Scene1.SetBlocks(blocks);
	Scene1.SetBalls(balls);
}
