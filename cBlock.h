#pragma once

#include "cData.h"

class cBlock
{
public:
    cBlock(void);
    virtual ~cBlock(void);
    void setPos(float x, float y, float z);
    void setColor(float r, float g, float b);
	void Draw();

private:
    float x, y, z, r, g, b;
	int id_DL;
};