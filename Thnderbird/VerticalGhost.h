#pragma once
#include "LineGhost.h"


class VerticalGhost : public LineGhost {

	char figure = (char)BoardFigure::VERTICAL_GHOST;
	int direction = (int)Direction::UP;

public:

	//ctors+dtors
	VerticalGhost() = default;
	VerticalGhost(char _figure, vector <Point*> _list_points, int _size);
	VerticalGhost(const VerticalGhost& _verticalGhost) = default;
	VerticalGhost& operator=(const VerticalGhost& _verticalGhost) = default;
	~VerticalGhost() override;

	char getFigure() override;
	int getDirection() override;
	void switchDirection() override;
	void checkGhostCollision(Board* board) override;
};