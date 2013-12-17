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

void cScene::Init()
{
	float x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	float y = -(SCENE_HEIGHT / 2.0) + (BLOCK_HEIGHT / 2.0);
	float z = (SCENE_DEPTH / 2.0) - (BLOCK_DEPTH / 2.0);

	float r, g, b;

	int num_block = 0;
	scene = std::vector<cBlock>(SCENE_DEPTH * 3 + SCENE_WIDTH + SCENE_DEPTH*(SCENE_WIDTH + 2));
	for (int i = 0; i < SCENE_DEPTH/BLOCK_DEPTH; ++i)
	{
		scene[num_block].setPos(x, y, z);

		r = (rand() % 256) / 256.0;
		g = (rand() % 256) / 256.0;
		b = (rand() % 256) / 256.0;

		(scene[num_block]).setColor(r, g, b);
		(scene[num_block]).setTex(IMG_GRASS_SIDE);
		++num_block;
		z -= BLOCK_DEPTH;
	}

	x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	y = -(SCENE_HEIGHT / 2.0) + (BLOCK_HEIGHT / 2.0);
	z = -(SCENE_DEPTH / 2.0) - (BLOCK_DEPTH / 2.0);

	for (int i = 0; i < (SCENE_WIDTH/BLOCK_WIDTH) + 2*BLOCK_WIDTH; ++i)
	{
		(scene[num_block]).setPos(x, y, z);

		r = (rand() % 256) / 256.0;
		g = (rand() % 256) / 256.0;
		b = (rand() % 256) / 256.0;

		(scene[num_block]).setColor(r, g, b);
		(scene[num_block]).setTex(IMG_GRASS_SIDE);
		++num_block;
		x += BLOCK_WIDTH;
	}

	x = (SCENE_WIDTH / 2.0) + (BLOCK_WIDTH / 2.0);
	y = -(SCENE_HEIGHT / 2.0) + (BLOCK_HEIGHT / 2.0);
	z = -(SCENE_DEPTH / 2.0) + (BLOCK_DEPTH / 2.0);

	for (int i = 0; i < SCENE_DEPTH/BLOCK_DEPTH; ++i)
	{
		(scene[num_block]).setPos(x, y, z);

		r = (rand() % 256) / 256.0;
		g = (rand() % 256) / 256.0;
		b = (rand() % 256) / 256.0;

		(scene[num_block]).setColor(r, g, b);
		(scene[num_block]).setTex(IMG_GRASS_SIDE);
		++num_block;
		z += BLOCK_DEPTH;
	}

	x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	y = -(SCENE_HEIGHT / 2.0) - (BLOCK_HEIGHT / 2.0);
	z = (SCENE_DEPTH / 2.0) - (BLOCK_DEPTH / 2.0);

	for (int i = 0; i < SCENE_DEPTH/BLOCK_DEPTH; ++i)
	{
		for (int j = 0; j < (SCENE_WIDTH/BLOCK_WIDTH) + 2*BLOCK_WIDTH; ++j)
		{
			(scene[num_block]).setPos(x, y, z);

			r = (rand() % 256) / 256.0;
			g = (rand() % 256) / 256.0;
			b = (rand() % 256) / 256.0;

			(scene[num_block]).setColor(r, g, b);
			(scene[num_block]).setTex(IMG_GRASS_SIDE);
			++num_block;
			x += BLOCK_WIDTH;
		}
		z -= BLOCK_DEPTH;
		x = -(SCENE_WIDTH / 2.0) - (BLOCK_WIDTH / 2.0);
	}
}

void cScene::Draw(cData *Data)
{
	for (int i = 0; i < SCENE_DEPTH/BLOCK_DEPTH; ++i)
	{
		scene[i].Draw(Data);
	}

	for (int i = SCENE_DEPTH/BLOCK_DEPTH; i < SCENE_WIDTH/BLOCK_WIDTH + SCENE_DEPTH/BLOCK_DEPTH + 2*BLOCK_DEPTH; ++i)
	{
		(scene[i]).Draw(Data);
	}

	for (int i = SCENE_WIDTH/BLOCK_WIDTH + SCENE_DEPTH/BLOCK_DEPTH + 2*BLOCK_DEPTH; i < SCENE_WIDTH/BLOCK_WIDTH + SCENE_DEPTH/BLOCK_DEPTH + 2*BLOCK_DEPTH + SCENE_DEPTH/BLOCK_DEPTH; ++i)
	{
		(scene[i]).Draw(Data);
	}

	for (int i = SCENE_WIDTH / BLOCK_WIDTH + SCENE_DEPTH / BLOCK_DEPTH + 2 * BLOCK_DEPTH + SCENE_DEPTH / BLOCK_DEPTH; i < SCENE_WIDTH / BLOCK_WIDTH + SCENE_DEPTH / BLOCK_DEPTH + 2 * BLOCK_DEPTH + SCENE_DEPTH / BLOCK_DEPTH + (SCENE_WIDTH/BLOCK_WIDTH + 2*BLOCK_WIDTH)*(SCENE_DEPTH/BLOCK_DEPTH); ++i)
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

        float x = BLOCK_WIDTH/2 - (SCENE_WIDTH/2);
        float y = -(SCENE_HEIGHT/2) + (BLOCK_HEIGHT/2.0);
		float z = -(BLOCK_DEPTH/2); //cambiar 0.5 por BLOCK_HEIGHT etc

        float r, g, b;
		blocks = std::vector<std::stack <cBlock> >(NUM_ROWS*NUM_COLUMNS);
        for (int i = 0; i < NUM_ROWS; ++i)
        {
			for (int j = 0; j < NUM_COLUMNS; ++j)
			{
				int altura = (rand() % 4);
				float ymax = y + altura*BLOCK_HEIGHT;
				altura++;
				for (int k = 1; k <= altura; ++k) {
					cBlock newBlock;
					newBlock.setPos(x, ymax, z);

					r = (rand() % 256) / 256.0;
					g = (rand() % 256) / 256.0;
					b = (rand() % 256) / 256.0;

					newBlock.setColor(r, g, b);
					int tex = rand() % 5;
					newBlock.setTex(tex);
					ymax -= BLOCK_HEIGHT;
					(blocks[num_block]).push(newBlock);
				}
				x += BLOCK_WIDTH;
				++num_block;
			}
			x = BLOCK_WIDTH / 2 - (SCENE_WIDTH / 2);
			z -= BLOCK_DEPTH;
        }

        num_blocks = num_block;
}

void cScene::RenderBlocks(cData *Data)
{
	std::vector<std::stack<cBlock> > blocksaux = blocks;
	for (int i = 0; i < num_blocks; ++i) {
		while (!blocksaux[i].empty()){
			blocksaux[i].top().Draw(Data);
			blocksaux[i].pop();
		}
	}
}

void cScene::RenderBalls()
{
	for(int i = 0; i<1; ++i) {
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

std::vector<std::stack <cBlock> > cScene::GetBlocks()
{
	return blocks;
}

void cScene::SetBlocks(std::vector<std::stack <cBlock> > blocks)
{
	this->blocks = blocks;
}