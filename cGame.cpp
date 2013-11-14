#include "cGame.h"
#include "Globals.h"


cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	bool res=true;

	azimut = 0;
	fita = 0;
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
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	if (keys[GLUT_KEY_UP])
	{
		++azimut;

		double r = sqrt((cam_x*cam_x + cam_y*cam_y + cam_z*cam_z));

		cam_x = r*cos(azimut)*sin(fita);
		cam_y = r*sin(fita);
		cam_z = r*cos(azimut)*cos(fita);
	}
	
	//Game Logic
	//...

	return res;
}

//Output
void cGame::Render()
{
	
	gluLookAt(cam_x, cam_y, cam_z, 0.0, -2.0, -40.0, 0.0, 1.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	
	glTranslatef(0.0f,-2.0f,-40.0f);
	glRotatef(20,1.0f,0.0f,0.0f);

	Scene.Draw(&Data);
	Scene.RenderBlocks();
	//Player.Draw(&Data);

	glutSwapBuffers();
}
