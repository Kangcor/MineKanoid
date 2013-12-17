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

	if (CornerInsideBox(izqBall, topBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((izqBall - derBlock) < (botBlock - topBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
	}
	else if (CornerInsideBox(derBall, topBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((derBall - izqBlock) < (botBlock - topBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
	}
	else if (CornerInsideBox(izqBall, botBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((izqBall - derBlock) < (topBlock - botBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
	}
	else if (CornerInsideBox(derBall, botBall, topBlock, botBlock, izqBlock, derBlock)) {
		if ((derBall - izqBlock) < (topBlock - botBall)) ball.setDif(ball.getDifX()*-1, ball.getDifZ());
		else ball.setDif(ball.getDifX(), ball.getDifZ()*-1);
		block.pinta = false;
	}
}

bool cPhysics::CornerInsideBox(float coordX, float coordZ, float top, float bot, float izq, float der)
{
	return (coordX > izq) && (coordX < der) && (coordZ > top) && (coordZ < bot);
}

void cPhysics::FallingBlocks(std::vector<std::stack <cBlock> > &blocks)
{
	for (int i = 0; i < NUM_ROWS*NUM_COLUMNS; ++i) {
		if (!blocks[i].top().pinta) {
			blocks[i].pop();
			blocks[i] = StackDown(blocks[i], BLOCK_HEIGHT / 60);
		}
	}
}

std::stack<cBlock> cPhysics::StackDown(std::stack<cBlock> blocks, float desc)
{
	std::stack<cBlock> stackAux;
	while (!blocks.empty()){
		cBlock block = blocks.top();
		block.setPos(block.getX(), block.getY() - desc, block.getZ());
		if (block.getY() > (-(SCENE_HEIGHT / 2) + (BLOCK_HEIGHT / 2.0))) block.cayendo = true;
		blocks.pop();
	}
	while (!stackAux.empty()){
		blocks.push(stackAux.top());
		stackAux.pop();
	}
	return blocks;
}