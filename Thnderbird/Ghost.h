#pragma once

#include "Point.h"

class Point;

class Ghost
{
public:

	//data members
	Point* point;
	char figure = (char)BoardFigure::Ghost;
	Color color = Color::BROWN;
	bool isBlock = false;
	int ghostId = (int)ObjectId::EMPTY;


	//ctors + dtors
	Ghost() = default;
	Ghost(Point* _point, int _ghostId);
	Ghost(Point* _point, char _figure, Color _color, bool _isBlock, int _ghostId);
	Ghost(const Ghost& _ghost) = default;
	Ghost& operator=(const Ghost& _ghost) = default;
	~Ghost();

private:

};
