#pragma once

#include "cBlock.h"
#include "cBall.h"
#include "cPlayer.h"
#include <vector>
#include <stack>

class cPhysics
{
public:
	cPhysics(void);
	virtual ~cPhysics(void);

	void CollidePlayer(cBall &ball, cPlayer &player);
	void CollideBlock(cBall &ball, cBlock &block);
	bool CornerInsideBox(float coordX, float coordZ, float top, float bot, float izq, float der);
	void FallingBlocks(std::vector<std::stack <cBlock> > &blocks);
	std::stack<cBlock> cPhysics::StackDown(std::stack<cBlock> blocks, float desc);
};
