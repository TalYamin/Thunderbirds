#pragma once
#include "Color.h"
#include "Point.h"
#include "ShipSize.h"
#include "Board.h"
#include "BoardFigure.h"
#include "ObjectId.h"
#define BIG_HORIZONTAL_SIZE 2
#define BIG_VERTICAL_SIZE 2
#define SMALL_HORIZONTAL_SIZE 2
#define SMALL_VERTICAL_SIZE 1
#define NUM_ARROW_KEYS 4
#define NO_DIRECTION -1

class Board;

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
	bool isShipBlock = false;
	bool isExit = false;
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
	void setIsExit(bool _isExit);
	bool getIsExit();
	void setShipMat(Board* board);
	Point** getShipMat();

	//public methods
	void move(Board* board);
	void initDraw();

private:

	//private methods
	void moveBigShip(Board* board);
	void moveSmallShip(Board* board);
	void checkSmallCollision(Board* board);
	void checkBigCollision(Board* board);
	
};

