#include "cPhysics.h"
#include "Globals.h"


cPhysics::cPhysics(void) {}
cPhysics::~cPhysics(void){}

void cPhysics::CollidePlayer(cBall &ball, cPlayer &player)
{
	float topBall = ball.getZ() - BALL_RADIUS;
	float botBall = ball.getZ() + BALL_RADIUS;
	float izqBall = ball.getX() - BALL_RADIUS;
	float derBall = ball.getX() + BALL_RADIUS;
	float topPlayer = (SCENE_DEPTH/2) - PLAYER_DEPTH/2;
	float botPlayer = (SCENE_DEPTH/2) + PLAYER_DEPTH/2;
	float izqPlayer = player.getPosition() - PLAYER_WIDTH/2;
	float derPlayer = player.getPosition() + PLAYER_WIDTH/2;

	if ((botBall > topPlayer) &&
		(((izqBall > izqPlayer)
		&& (izqBall < derPlayer))
		|| ((derBall < izqPlayer)
		&& (derBall > derPlayer)))) {
			if (izqBall > derPlayer - (PLAYER_WIDTH/3)) ball.setDif(0.07, -0.03);
			else if (derBall < izqPlayer + (PLAYER_WIDTH / 3)) ball.setDif(-0.07, -0.03);
			else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
	}
	ball.setPos(ball.getX() + ball.getDifX(), ball.getZ() + ball.getDifZ());

	if(ball.getX() > SCENE_WIDTH/2) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
	if(ball.getX() < -SCENE_WIDTH/2) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
	if(ball.getZ() < -SCENE_DEPTH/2) ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
	if(ball.getZ() > (SCENE_DEPTH/2)+2) {
		ball.setPos(0.0, 12.0);
		ball.setDif(0.05, 0.05);
	}
}

void cPhysics::CollideBlock(cBall &ball, cBlock &block)
{
	float topBall = ball.getZ() - BALL_RADIUS;
	float botBall = ball.getZ() + BALL_RADIUS;
	float izqBall = ball.getX() - BALL_RADIUS;
	float derBall = ball.getX() + BALL_RADIUS;
	float topBlock = block.getZ() - BLOCK_DEPTH / 2.0;
	float botBlock = block.getZ() + BLOCK_DEPTH / 2.0;	
	float izqBlock = block.getX() - BLOCK_WIDTH / 2.0;
	float derBlock = block.getX() + BLOCK_WIDTH / 2.0;

	float minx1 = izqBall;
	float minz1 = topBall;
	float maxx1 = derBall;
	float maxz1 = botBall;
	float minx2 = izqBlock;
	float minz2 = topBlock;
	float maxx2 = derBlock;
	float maxz2 = botBlock;
	if ((minx1 < maxx2) && (minx2 < maxx1) && (minz1 < maxz2) && (minz2 < maxz1)) {
		block.pinta = false;
	//	block.cayendo = true;
		block.explosion = 0;
		if (min(abs(minx1 - maxx2), abs(minx2 - maxx1) < min(abs(minz1 - maxz2), abs(minz2 - maxz1)))) {
			ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		}
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
	}
	
	/*
	if (CornerInsideBox(izqBall, topBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((izqBall - derBlock) < (botBlock - topBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
		block.explosion = 0;
	}
	else if (CornerInsideBox(derBall, topBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((derBall - izqBlock) < (botBlock - topBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
		block.explosion = 0;
	}
	else if (CornerInsideBox(izqBall, botBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((izqBall - derBlock) < (topBlock - botBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
		block.explosion = 0;
	}
	else if (CornerInsideBox(derBall, botBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((derBall - izqBlock) < (topBlock - botBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
		block.explosion = 0;
	}*/
}

bool cPhysics::CornerInsideBox(float coordX, float coordZ, float top, float bot, float izq, float der)
{
	return (coordX > izq) && (coordX < der) && (coordZ > top) && (coordZ < bot);
}

void cPhysics::FallingBlocks(std::vector<std::vector <cBlock> > &blocks)
{
	for (int i = 0; i < NUM_ROWS*NUM_COLUMNS; ++i) {
		if (!blocks[i][0].pinta) {
			if (blocks[i][0].cayendo) {
				for (int j = 0; j < blocks[i].size(); ++j) {
					blocks[i][0].cayendo = StackDown(blocks[i][j], BLOCK_HEIGHT /180);
				}
			}
		}
	}
}

bool cPhysics::StackDown(cBlock &block, float desc)
{
	block.setPos(block.getX(), block.getY() - desc, block.getZ());
	return !(block.getY() <= (-(SCENE_HEIGHT / 2) + (BLOCK_HEIGHT / 2.0)));
}