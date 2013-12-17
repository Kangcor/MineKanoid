#pragma once

#include "cData.h"
#include "cBlock.h"
#include "cBall.h"
#include <vector>
#include <stack>

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	void Init();
	void Draw(cData *Data);

	void InitBlocks(int level);

	void RenderBlocks(cData *Data);
	void RenderBalls();
	
	std::vector<cBall> GetBalls();  
	void SetBalls(std::vector<cBall> balls);

	std::vector<std::stack <cBlock> > GetBlocks();
	void SetBlocks(std::vector<std::stack <cBlock> > blocks);

	
private:

	std::vector<cBall> balls;
	std::vector<std::stack <cBlock> > blocks;
	std::vector<cBlock> scene;
    int num_blocks;

};
