#pragma once

#include "cData.h"

class cBlock
{
public:
    cBlock(void);
    virtual ~cBlock(void);
	void setTex(int tex);
    void setPos(float x, float y, float z);
	float getX();
	float getZ();
    void setColor(float r, float g, float b);
	void Draw(cData *Data);
	float r, g, b;
	bool pinta;

private:
	float x, y, z;
	int id_DL;
	int tex;
};