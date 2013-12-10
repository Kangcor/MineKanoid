#pragma once

#include "cBall.h"
#include "cPlayer.h"

class cPhysics
{
public:
	cPhysics(void);
	virtual ~cPhysics(void);

	bool Collide(cBall ball, cPlayer player);
};
