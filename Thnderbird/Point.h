#pragma once

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point
{
	int x = 1;
	int y = 1;
	char figure = ' ';
public:
	void setX(int _x);
	void setY(int _y);
	int getX();
	int getY();
	void draw();
	void draw(char _fig);
	void move(int direction);
	char getFigure();
	Point(int _x, int _y);
	Point(int _x, int _y, char _fig);
	~Point() {};
	Point() = default;
	Point(const Point& _p) = default;
	Point& operator=(const Point& _p) = default;
private:

};


