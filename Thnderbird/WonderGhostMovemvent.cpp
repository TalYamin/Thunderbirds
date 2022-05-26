#include "WonderGhostMovemvent.h"

WonderGhostMovemvent::WonderGhostMovemvent(int _objectId, int _direction)
{
	objectId = _objectId;
	direction = _direction;
}

WonderGhostMovemvent::~WonderGhostMovemvent()
{
}

int WonderGhostMovemvent::getObjcetId()
{
	return objectId;
}
