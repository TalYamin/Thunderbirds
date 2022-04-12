#pragma once

#include "Point.h"
#include "Board.h"
#include "Direction.h"

class Point;

class Ghost
{
public:

	//data members
	Point** list_points;
	char figure = (char)BoardFigure::HORIZONTAL_GHOST;
	Color color = Color::BROWN;
	bool isGhostBlock = false;
	int ghostId = (int)ObjectId::EMPTY;
	static int idGenerator;
	int direction = (int)Direction::RIGHT;
	int size = 0;


	//ctors + dtors
	Ghost() = default;
	Ghost(Point** _list_points, int _size);
	Ghost(Point** _list_points, char _figure, Color _color, bool _isGhostBlock, int _ghostId);
	Ghost(const Ghost& _ghost) = default;
	Ghost& operator=(const Ghost& _ghost) = default;
	~Ghost();


	//public methods
	void Move(Board* board);
	int getSize();

private:

	//private methods
	void MoveGhost(Board* board);
	void checkGhostCollision(Board* board);
	void switchDirection();
};
