#pragma once
#include "Color.h"
#include "Point.h"
#include "ShipSize.h"
#include "Board.h"
#include "BoardFigure.h"
#include "ObjectId.h"
#include <vector>
#define BIG_HORIZONTAL_SIZE 2
#define BIG_VERTICAL_SIZE 2
#define SMALL_HORIZONTAL_SIZE 2
#define SMALL_VERTICAL_SIZE 1
#define NUM_ARROW_KEYS 4
#define NO_DIRECTION -1

class Board;
class Block;

class SpaceShip
{

	//date members 
	ShipSize type = ShipSize::UNDEFINED;
	int verticalSize = 2;
	int horizontalSize = 2;
	int direction = (int)Direction::RIGHT;
	char figure = (char)BoardFigure::BIG_SHIP;
	char arrowKeys[NUM_ARROW_KEYS] = { 'w','x','a','d' };
	Color color = Color::GREEN;
	bool isShipBlock = false;
	bool isExit = false;
	bool isDie = false;
	Point* shipMat[2] = {};
	int maxCarringBlockSize = 6;


public:

	//ctor + dtor
	SpaceShip() = default;
	SpaceShip(const SpaceShip& _spaceship) = default;
	SpaceShip& operator=(const SpaceShip& _spaceship);
	SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color, int _maxCarringBlockSize, ShipSize _type);
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
	void setIsDie(bool _isDie);
	bool getIsDie() const;
	void setupShipMat(int x, int y);
	Point** getShipMat();

	//public methods
	void move(Board* board);
	void initDraw() const;
	char getCurrentDirectionKey();

private:

	//private methods
	void moveShip(Board* board, ObjectId type);
	void checkCollision(Board* board);
	bool checkShipMatPointCollision(Board* board, int x, int y, vector<Block*>& blocksInvolve, bool* isGhost, bool& isWallIsInvolved);
	void shipCanPushMultipleBlocks(Board* board, vector<Block*>& blocksInvolve);
	void checkWallInvolvement(Board* board, int x, int y, bool& isWallIsInvolved);
};

