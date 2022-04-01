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
	bool isBlock = false;
	bool isExit = false;
	Point* shipMat[2];
	

public:

	//ctor + dtor
	SpaceShip();
	SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color);
	~SpaceShip();

	//getters + setters
	void setType(int typeNum);
	ShipSize getType() const;
	void setVerticalSize(int _verticalSize);
	int getVerticalSize() const;
	void setHorizontalSize(int _horizontalSize);
	int getHorizontalSize() const;
	void setDirection(int _direction);
	int getDirection(char key) const;
	void setFigure(const char c);
	char getFigure() const;
	void setArrowKeys(const char* keys);
	void setColor(Color _color);
	Color getColor() const;
	void setIsBlock();
	bool getIsBlock() const;
	void setIsExit(bool _isExit);
	bool getIsExit() const;
	void setShipMat(Board* board);
	Point** getShipMat();

	//public methods
	void move(Board* board);
	void initDraw() const;

private:

	//private methods
	void moveBigShip(Board* board);
	void moveSmallShip(Board* board);
	void checkSmallCollision(Board* board);
	void checkSBigCollision(Board* board);
	
};

