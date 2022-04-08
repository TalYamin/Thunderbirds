#pragma once

#include "Point.h"

class Point;

class Ghost
{
public:

	//data members
	Point* point;
	char figure = (char)BoardFigure::HORIZONTAL_GHOST;
	Color color = Color::BROWN;
	bool isBlock = false;
	int ghostId = (int)ObjectId::EMPTY;
	static int idGenerator;


	//ctors + dtors
	Ghost() = default;
	Ghost(Point* _point);
	Ghost(Point* _point, char _figure, Color _color, bool _isBlock, int _ghostId);
	Ghost(const Ghost& _ghost) = default;
	Ghost& operator=(const Ghost& _ghost) = default;
	~Ghost();

private:

};
