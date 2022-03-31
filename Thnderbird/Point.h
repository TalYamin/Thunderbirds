#pragma once

#include <iostream>
#include "io_utils.h"
#include "ObjectId.h"

using namespace std;

class Point
{
	int objectId = -1;
	int x = 1;
	int y = 1; 
	char figure = ' ';
	Color color = Color::WHITE;
public:
	void setX(int _x);
	void setY(int _y);
	int getX();
	int getY();
	void setObjecId(int _objectId);
	int getObjecId();
	void draw() const;
	void draw(char _fig);
	void move(int direction);
	char getFigure();
	void setFigure(char _figure);
	Point(int _x, int _y);
	Point(int _x, int _y, char _fig);
	Point(int _x, int _y, char _fig, Color _color, int _objectId);
	~Point() {};
	Point() = default;
	Point(const Point& _p) = default;
	Point& operator=(const Point& _p) = default;
private:

};


