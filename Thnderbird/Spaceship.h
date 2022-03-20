#pragma once
#include "Color.h"
#include "Point.h"

class SpaceShip
{
	enum class ShipSize { SMALL = 1, BIG = 2 };
	int verticalSize;
	int horizontalSize;
	int direction = 3;
	char figure;
	char arrowKeys[4] = { 0,1,2,3 };
	Color color;
	bool isBlock;
	Point* mat[2];
public:
	void setArrowKeys(const char* keys) { // "wzad"
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	};
	void setColor(Color c) { color = c; };
	void setFigure(const char c) { figure = c; };
	void move();
	int getDirection(char key) { return key; };
	void setDirection(int dir) { direction = dir; };
	void setIsBlock() {
		isBlock == true ? isBlock = false : isBlock = true;
	};
	SpaceShip();
	~SpaceShip();

private:

};

