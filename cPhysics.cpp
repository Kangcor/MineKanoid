#include "cPhysics.h"
#include "Globals.h"


cPhysics::cPhysics(void) {}
cPhysics::~cPhysics(void){}

bool cPhysics::Collide(cBall ball, cPlayer player)
{
	if (player.getPosition() == ball.getX()) return true;
	else return false;
}