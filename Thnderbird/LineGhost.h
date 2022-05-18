#pragma once
#include "Ghost.h"


class LineGhost : public Ghost {

public:

	//ctors + dtors
	LineGhost() = default;
	LineGhost(vector <Point*> _list_points, int _size);
	virtual ~LineGhost();

	//public functions
	void Move(Board* board) override;

};