#pragma once
#include "WonderGhostMovement.h"
#include <vector>


using namespace std;

class MoveIteration
{
	int key;
	vector<WonderGhostMovemvent*> wonderGhostMovemvent;
public:
	MoveIteration(int _key, vector<WonderGhostMovemvent*> _wgm);
	~MoveIteration();

private:

};

