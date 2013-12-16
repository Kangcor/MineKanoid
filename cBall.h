#pragma once

class cBall
{
public:
	cBall(void);
	virtual ~cBall(void);
	void setPos(float x, float z);
	void setDif(float difX, float difZ);
	void setColor(float r, float g, float b);
	void Draw();
	float getX();
	float getZ();
	float getDifX();
	float getDifZ();
	void Logic(float position);

private:
	float x, y, z, r, g, b;
	float difX, difZ;
	float velocity;
};
