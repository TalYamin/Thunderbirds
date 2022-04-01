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
	int maxCarringBlockSize = 6;
	

public:

	//ctor + dtor
	SpaceShip() = default;
	SpaceShip(const SpaceShip& _spaceship) = default;
	SpaceShip& operator=(const SpaceShip& _spaceship) = default;
	SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color, int _maxCarringBlockSize);
	~SpaceShip();

	//getters + setters
	int getMaxCarringBlockSize();
	void setMaxCarringBlockSize(int _maxCarringBlockSize);
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
	void setIsShipBlock();
	bool getIsShipBlock() const;
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
	void checkBigCollision(Board* board);
	
};

