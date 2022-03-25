#pragma once
#include "Color.h"
#include "Point.h"
#include "ShipSize.h"
class SpaceShip
{

	//date members 
	ShipSize type;
	int verticalSize;
	int horizontalSize;
	int direction;
	char figure;
	char arrowKeys[4];
	Color color;
	bool isBlock = false;
	Point* mat[2];

public:

	//ctor + dtor
	SpaceShip();
	SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color);
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
	void initDraw(ShipSize size);


private:

	//private methods
	void moveBigShip();
	void moveSmallShip();

};

