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

	void Init(int scene_type);
	void Draw(cData *Data);

	void InitBlocks(int level);
	void InitWin();
	void RenderWin(cData *Data);
	void RenderBlocks(cData *Data);
	void RenderBalls();
	
	std::vector<cBall> GetBalls();  
	void SetBalls(std::vector<cBall> balls);

	std::vector<std::vector <cBlock> > GetBlocks();
	void SetBlocks(std::vector<std::vector <cBlock> > blocks);

	
private:

	std::vector<cBall> balls;
	std::vector<std::vector <cBlock> > blocks;
	std::vector<cBlock> scene;
	std::vector<cBlock> win;
    int num_blocks;
	int num_blocks_secene;
	int num_blocks_win;
	int scene_type;
};
