#include "MoveIteration.h"


MoveIteration::MoveIteration(int _key, vector<WonderGhostMovemvent*> _wgm)
{
	key = _key;
	for (int i = 0;i < _wgm.size();i++)
		wonderGhostMovemvent.push_back(_wgm[i]);
}

MoveIteration::~MoveIteration()
{
}