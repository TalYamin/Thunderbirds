#pragma once

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point
{
	int x = 1;
	int y = 1;
public:
	void draw(char ch);
	void move(int direction);
	Point() {};
	Point(int _x, int _y);
	~Point() {};
private:

};


