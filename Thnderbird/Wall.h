#pragma once
#include "Point.h"
#include "Color.h"

class Wall
{
	Point point;
	Color color;
	char figure = '#';
public:
	Wall(Point _point, Color _color);
	Wall(Point _point, Color _color, char _figure);


private:

};

