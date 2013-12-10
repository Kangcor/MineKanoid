#pragma once

#include "cData.h"

class cPlayer
{
public:
	cPlayer(void);
	virtual ~cPlayer(void);
	
	void setPosition(float postion);
	float getPosition();

	void Draw(cData *Data);
private:
	float position;
};
