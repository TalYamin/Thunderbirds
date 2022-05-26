#pragma once
#include "Ghost.h"
class WonderGhost : public Ghost
{
	char figure = (char)BoardFigure::WANDER_GHOST;
	int direction = (int)Direction::UP;
public:
	WonderGhost(char _figure, vector<Point*> _list_points, int _seed);
	~WonderGhost() override;

	char getFigure() override;
	int getDirection() override;
	void switchDirection() override;
	void checkGhostCollision(Board* board) override;
	void Move(Board* board) override;
private:

};
