#pragma once

#include "cData.h"

class cBlock
{
public:
	cBlock(void);
	virtual ~cBlock(void);
	void setPos(float x, float y, float z);
	void Draw();
	void initBlock();

private:
	float x, y, z;
	int id_DL;
};
