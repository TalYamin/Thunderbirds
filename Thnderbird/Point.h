#pragma once

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point
{
	int x = 1;
	int y = 1;
public:
	void setX(int _x);
	void setY(int _y);
	void draw(char ch);
	void move(int direction);
	Point(int _x, int _y);
	~Point() {};
	Point() = default;
	Point(const Point & _p) = default;
	Point& operator=(const Point & _p) = default;
private:

};


