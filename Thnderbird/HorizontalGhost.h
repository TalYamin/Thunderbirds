#pragma once
#include "LineGhost.h"


class HorizontalGhost : public LineGhost {

	char figure = (char)BoardFigure::HORIZONTAL_GHOST; 
	int direction = (int)Direction::RIGHT;

public:

	//ctors+dtors
	HorizontalGhost() = default;
	HorizontalGhost(char _figure, vector <Point*> _list_points, int _size);
	HorizontalGhost(const HorizontalGhost& _horizontalGhost) = default;
	HorizontalGhost& operator=(const HorizontalGhost& _horizontalGhost) = default;
	~HorizontalGhost() override;

	char getFigure() override;
	int getDirection() override;
	void switchDirection() override;
	void checkGhostCollision(Board* board) override;
};