#pragma once

#include "cData.h"
#include "cParticle.h"

class cBlock
{
public:
    cBlock(void);
    virtual ~cBlock(void);
	void setTex(int tex);
    void setPos(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
    void setColor(float r, float g, float b);
	void Draw(cData *Data);
	void DrawParticle();
	float r, g, b;
	bool pinta;
	bool cayendo;
	int explosion;

private:
	float x, y, z;
	int id_DL;
	int tex;
	cParticle particula;
};