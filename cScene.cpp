#include "cScene.h"
#include "Globals.h"

cScene::cScene(void) 
{
	ball = std::vector<cBall> (10);
	ball[0].setPos(0, 12);
	ball[1].setPos(2, -4);
	ball[2].setPos(4, -6);
	ball[3].setPos(6, -14);
	ball[4].setPos(8, -3);
	ball[5].setPos(10, 8);
	ball[6].setPos(-5, -2);
	ball[7].setPos(-8, 5);
	ball[8].setPos(-12, -13);
	ball[9].setPos(-2, 2);

	
    InitBlocks(1);
	
}
cScene::~cScene(void){}

void cScene::Draw(cData *Data)
{
	float d  = SCENE_DEPTH/2.0f,
		  w  = SCENE_WIDTH/2.0f,
		  h  = SCENE_HEIGHT/2.0f,
		  //Tiling
		  td = SCENE_DEPTH/4.0f,
		  tw = SCENE_WIDTH/4.0f,
		  th = SCENE_HEIGHT/4.0f;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL));
	glBegin(GL_QUADS);
		// Front Face
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h,  d);
//		glTexCoord2f(  tw, 0.0f); glVertex3f( w, -h,  d);
//		glTexCoord2f(  tw,   th); glVertex3f( w,  h,  d);
//		glTexCoord2f(0.0f,   th); glVertex3f(-w,  h,  d);
		// Back Face
		glTexCoord2f(  tw, 0.0f); glVertex3f(-w, -h, -d);
		glTexCoord2f(  tw,   th); glVertex3f(-w,  h, -d);
		glTexCoord2f(0.0f,   th); glVertex3f( w,  h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h, -d);
		// Right face
		glTexCoord2f(  td, 0.0f); glVertex3f( w, -h, -d);
		glTexCoord2f(  td,   th); glVertex3f( w,  h, -d);
		glTexCoord2f(0.0f,   th); glVertex3f( w,  h,  d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, -d);
		glTexCoord2f(  td, 0.0f); glVertex3f(-w, -h,  d);
		glTexCoord2f(  td,   th); glVertex3f(-w,  h,  d);
		glTexCoord2f(0.0f,   th); glVertex3f(-w,  h, -d);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_FLOOR));
	glBegin(GL_QUADS);
		// Bottom Face
		glTexCoord2f(  tw,   td); glVertex3f(-w, -h, -d);
		glTexCoord2f(0.0f,   td); glVertex3f( w, -h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f(-w, -h,  d);
	glEnd();
	/*
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_ROOF));
	glBegin(GL_QUADS);
		// Top Face
		glTexCoord2f(0.0f,   td); glVertex3f(-w,  h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w,  h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f( w,  h,  d);
		glTexCoord2f(  tw,   td); glVertex3f( w,  h, -d);
	glEnd();
	*/
	glDisable(GL_TEXTURE_2D);

	
}

void cScene::InitBlocks(int level)
{
        bool res;
        FILE *fd;
        char file[16];
        char char_aux;
        int rows, columns, num_block;
        num_block = 0;
        rows = 16;
        columns = 16;

        float x = 0.5 - (SCENE_WIDTH/2);
        float y = -(SCENE_HEIGHT/2) + (BLOCK_HEIGHT/2.0);
        float z = -0.5; //cambiar 0.5 por BLOCK_HEIGHT etc

        float r, g, b;

        for (int i = 0; i < rows; ++i)
        {
                for (int j = 0; j < columns; ++j)
                {
                        blocks[num_block] = new cBlock();
                        (*blocks[num_block]).setPos(x, y, z);

                        r = (rand() % 256)/256.0;
                        g = (rand() % 256)/256.0;
                        b = (rand() % 256)/256.0;

                        (*blocks[num_block]).setColor(r,g,b);
                        x += 1;
                        ++num_block;
                }
                x = 0.5 - (SCENE_WIDTH / 2);
                z -= 1;
        }

        num_blocks = num_block;
}

void cScene::RenderBlocks()
{
	for (int i = 0; i < num_blocks; ++i) (*blocks[i]).Draw();
}

void cScene::RenderBalls(float position)
{
	for(int i = 0; i<10; ++i) {
		ball[i].Logic(position);
		ball[i].Draw();
	}
}

std::vector<cBall> cScene::GetBalls()
{
	return ball;
}

void cScene::SetBalls(std::vector<cBall> balls)
{
	ball = balls;
}