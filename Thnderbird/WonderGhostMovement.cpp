#include "WonderGhostMovement.h"

WonderGhostMovemvent::WonderGhostMovemvent()
{
}

WonderGhostMovemvent::WonderGhostMovemvent(int _obejctId, int _direction)
{
	objectId = _obejctId;
	direction = _direction;
}


WonderGhostMovemvent::~WonderGhostMovemvent()
{
}

int WonderGhostMovemvent::getObjectId()
{
	return objectId;
}

int WonderGhostMovemvent::getDirection()
{
	return direction;
}
