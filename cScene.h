#pragma once

#include "cData.h"
#include "cBlock.h"
#include "cBall.h"
#include <vector>

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool Init();
	void Draw(cData *Data);

	void InitBlocks(int level);

	void RenderBlocks();
	void RenderBalls(float position);
	
	std::vector<cBall> GetBalls();  
	void SetBalls(std::vector<cBall> balls);
	
private:

	std::vector<cBall> ball;
	cBlock *blocks[16*16];
    cBlock block;
    int num_blocks;

};
