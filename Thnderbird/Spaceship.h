#pragma once
#include "Color.h"
#include "Point.h"

class SpaceShip
{
	enum class ShipSize { SMALL = 1, BIG = 2 };
	ShipSize type;
	int verticalSize;
	int horizontalSize;
	int direction = 3;
	char figure;
	char arrowKeys[4] = { 0,1,2,3 };
	Color color;
	bool isBlock;
	Point* mat[2];

public:

	//ctor + dtor
	SpaceShip();
	~SpaceShip();

	//getters + setters
	void setType(int typeNum);
	ShipSize getType();
	void setVerticalSize(int _verticalSize);
	int getVerticalSize();
	void setHorizontalSize(int _horizontalSize);
	int getHorizontalSize();
	void setDirection(int _direction);
	int getDirection(char key);
	void setFigure(const char c);
	char getFigure();
	void setArrowKeys(const char* keys);
	void setColor(Color _color);
	Color getColor();
	void setIsBlock();
	bool getIsBlock();
	void setMat(ShipSize size);
	Point** getMat();

	//public methods
	void move(ShipSize size);
	

private:

	//private methods
	void moveSmallShip();
};

