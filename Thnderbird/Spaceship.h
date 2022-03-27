#pragma once
#include "Color.h"
#include "Point.h"
#include "ShipSize.h"
#include "Board.h"
#include "BoardFigure.h"
#define BIG_HORIZONTAL_SIZE 2
#define BIG_VERTICAL_SIZE 2
#define SMALL_HORIZONTAL_SIZE 2
#define SMALL_VERTICAL_SIZE 1


class SpaceShip
{

	//date members 
	ShipSize type = ShipSize:: UNDEFINED;
	int verticalSize;
	int horizontalSize;
	int direction = 3;
	char figure = ' ';
	char arrowKeys[4];
	Color color;
	bool isBlock = false;
	Point* shipMat[2];
	

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
	void setMat(ShipSize size, Board* board);
	Point** getMat();

	//public methods
	void move(ShipSize size, Board* board);
	void initDraw(ShipSize size);

private:

	//private methods
	void moveBigShip(Board* board);
	void moveSmallShip(Board* board);
	void checkSmalldWallCollision(Board* board);
	void checkSBigdWallCollision(Board* board);
	
};

