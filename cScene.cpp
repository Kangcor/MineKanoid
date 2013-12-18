#include "cScene.h"
#include "Globals.h"

cScene::cScene(void) 
{
	balls = std::vector<cBall> (10);
	balls[0].setPos(0, 12);
//	ball[1].setPos(2, -4);
//	ball[2].setPos(4, -6);
//	ball[3].setPos(6, -14);
//	ball[4].setPos(8, -3);
//	ball[5].setPos(10, 8);
//	ball[6].setPos(-5, -2);
//	ball[7].setPos(-8, 5);
//	ball[8].setPos(-12, -13);
//	ball[9].setPos(-2, 2);

	
    InitBlocks(1);
	
}
cScene::~cScene(void){}

void cScene::Init(int scene_type)
{
	this->scene_type = scene_type;

	float x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	float y = -(SCENE_HEIGHT / 2.0) + (BLOCK_HEIGHT / 2.0);
	float z = (SCENE_DEPTH / 2.0) - (BLOCK_DEPTH / 2.0);

	float r, g, b;

	int num_block = 0;
	scene = std::vector<cBlock>(SCENE_DEPTH*2 + SCENE_WIDTH + SCENE_DEPTH*(SCENE_WIDTH + 2));
	for (int i = 0; i < SCENE_DEPTH/BLOCK_DEPTH; ++i)
	{
		scene[num_block].setPos(x, y, z);

		r = (rand() % 256) / 256.0;
		g = (rand() % 256) / 256.0;
		b = (rand() % 256) / 256.0;

		(scene[num_block]).setColor(r, g, b);

		if (this->scene_type == 0) (scene[num_block]).setTex(IMG_GRASS_SIDE);
		else if (this->scene_type == 1) (scene[num_block]).setTex(IMG_WOOD);
		else (scene[num_block]).setTex(IMG_COPPER);

		++num_block;
		z -= BLOCK_DEPTH;
	}

	x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	y = -(SCENE_HEIGHT / 2.0) + (BLOCK_HEIGHT / 2.0);
	z = -(SCENE_DEPTH / 2.0) - (BLOCK_DEPTH / 2.0);

	for (int i = 0; i < (SCENE_WIDTH/BLOCK_WIDTH); ++i)
	{
		(scene[num_block]).setPos(x, y, z);

		r = (rand() % 256) / 256.0;
		g = (rand() % 256) / 256.0;
		b = (rand() % 256) / 256.0;

		(scene[num_block]).setColor(r, g, b);

		if (this->scene_type == 0) (scene[num_block]).setTex(IMG_GRASS_SIDE);
		else if (this->scene_type == 1) (scene[num_block]).setTex(IMG_WOOD);
		else (scene[num_block]).setTex(IMG_COPPER);

		++num_block;
		x += BLOCK_WIDTH;
	}

	x = (SCENE_WIDTH / 2.0) + (BLOCK_WIDTH / 2.0);
	y = -(SCENE_HEIGHT / 2.0) + (BLOCK_HEIGHT / 2.0);
	z = -(SCENE_DEPTH / 2.0) + (BLOCK_DEPTH / 2.0);

	for (int i = 0; i < SCENE_DEPTH/BLOCK_DEPTH ; ++i)
	{
		(scene[num_block]).setPos(x, y, z);

		r = (rand() % 256) / 256.0;
		g = (rand() % 256) / 256.0;
		b = (rand() % 256) / 256.0;

		(scene[num_block]).setColor(r, g, b);

		if (this->scene_type == 0) (scene[num_block]).setTex(IMG_GRASS_SIDE);
		else if (this->scene_type == 1) (scene[num_block]).setTex(IMG_WOOD);
		else (scene[num_block]).setTex(IMG_COPPER);

		++num_block;
		z += BLOCK_DEPTH;
	}

	x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	y = -(SCENE_HEIGHT / 2.0) - (BLOCK_HEIGHT / 2.0);
	z = (SCENE_DEPTH / 2.0) - (BLOCK_DEPTH / 2.0);

	for (int i = 0; i < SCENE_DEPTH/BLOCK_DEPTH; ++i)
	{
		for (int j = 0; j < (SCENE_WIDTH/BLOCK_WIDTH) + BLOCK_WIDTH; ++j)
		{
			(scene[num_block]).setPos(x, y, z);

			r = (rand() % 256) / 256.0;
			g = (rand() % 256) / 256.0;
			b = (rand() % 256) / 256.0;

			(scene[num_block]).setColor(r, g, b);

			if (this->scene_type == 0) (scene[num_block]).setTex(IMG_GRASS_SIDE);
			else if (this->scene_type == 1) (scene[num_block]).setTex(IMG_WOOD);
			else (scene[num_block]).setTex(IMG_COPPER);

			++num_block;
			x += BLOCK_WIDTH;
		}
		z -= BLOCK_DEPTH;
		x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	}

	num_blocks_secene = num_block;

	InitWin();
}

void cScene::Draw(cData *Data)
{
	for (int i = 0; i < num_blocks_secene; ++i)
	{
		(scene[i]).Draw(Data);
	}
}

void cScene::InitBlocks(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	char char_aux;
	int num_block = 0;

	float x = BLOCK_WIDTH / 2 - (SCENE_WIDTH / 2);
	float y = -(SCENE_HEIGHT / 2) + (BLOCK_HEIGHT / 2.0);
	float z = -(BLOCK_DEPTH / 2); //cambiar 0.5 por BLOCK_HEIGHT etc

	float r, g, b;
	blocks = std::vector<std::vector <cBlock> >(NUM_ROWS*NUM_COLUMNS);
	for (int i = 0; i < NUM_ROWS; ++i)
	{

		for (int j = 0; j < NUM_COLUMNS; ++j)
		{
			y = -(SCENE_HEIGHT / 2) + (BLOCK_HEIGHT / 2.0);
			int altura = (rand() % 4);
			altura++;
			std::vector<cBlock> colBlock(altura);
			for (int k = 0; k < altura; ++k) {
				colBlock[k].setPos(x, y, z);

				r = (rand() % 256) / 256.0;
				g = (rand() % 256) / 256.0;
				b = (rand() % 256) / 256.0;

				colBlock[k].setColor(r, g, b);
				int tex = rand() % 5;
				colBlock[k].setTex(tex);
				y += BLOCK_HEIGHT;
			}
			(blocks[num_block]) = colBlock;
			x += BLOCK_WIDTH;
			++num_block;
		}
		x = BLOCK_WIDTH / 2 - (SCENE_WIDTH / 2);
		z -= BLOCK_DEPTH;
	}

	num_blocks = num_block;
}

void cScene::InitWin()
{
	int num_block = 0;
	
	num_blocks_win = 0;

	float x = -SCENE_WIDTH/2;
	float y = 0;
	float z = 0;

	float r, g, b;
	win = std::vector<cBlock>(3*SCENE_WIDTH);

	std::vector<std::vector<int> > palabra = { { 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1 },
											   { 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1 },
											   { 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 } };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (palabra[i][j] == 1)
			{
				win[num_block].setPos(x, y, z);
				r = (rand() % 256) / 256.0;
				g = (rand() % 256) / 256.0;
				b = (rand() % 256) / 256.0;

				win[num_block].setColor(r, g, b);
				win[num_block].setTex(IMG_GOLD);
				++num_block;
			}
			x += BLOCK_WIDTH;
		}
		x = -SCENE_WIDTH/2;
		y += BLOCK_WIDTH;
	}

	num_blocks_win = num_block;
}

void cScene::RenderWin(cData *Data)
{
	
	for (int i = 0; i < num_blocks_win; ++i) win[i].Draw(Data);
	glPopMatrix();
}

void cScene::RenderBlocks(cData *Data)
{
	for (int i = 0; i < num_blocks; ++i) {
		for (int j = 0; j < blocks[i].size(); ++j) {
			if(blocks[i][j].pinta) blocks[i][j].Draw(Data);
			else if (blocks[i][j].explosion < 20)
			{
				blocks[i][j].DrawParticle();
				blocks[i][j].explosion++;
			}
		}
	}
}

void cScene::RenderBalls()
{
	for (int i = 0; i < 1; ++i) {
		balls[i].Draw();
	}
}

std::vector<cBall> cScene::GetBalls()
{
	return balls;
}

void cScene::SetBalls(std::vector<cBall> balls)
{
	this->balls = balls;
}

std::vector<std::vector <cBlock> > cScene::GetBlocks()
{
	return blocks;
}

void cScene::SetBlocks(std::vector<std::vector <cBlock> > blocks)
{
	this->blocks = blocks;
}