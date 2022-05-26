#pragma once
#include "Direction.h"

class WonderGhostMovemvent
{
	int objectId;
	int direction;
public:
	WonderGhostMovemvent();
	WonderGhostMovemvent(int _obejctId,int _direction);
	~WonderGhostMovemvent();
	int getObjectId();
	int getDirection();

private:

};
