#pragma once
#define HORIZONTAL_SIZE 80
#define VERTICAL_SIZE 25
#define LIVES_X 30
#define LIVES_Y 29
#define TIME_X 30
#define TIME_Y 30
#define SHIP_ICON_X 30
#define SHIP_ICON_Y 31
#define SPACE_BETWEEN_METADATA 20
#define LOG_X 30
#define LOG_Y 33
#define EXIT_Y 25
#define EXIT_X1 42
#define EXIT_X2 43
#define EXIT_X3 44
#define BLOCKS_AMOUNT 3
#define MAX_TIME 10000

#include "Point.h"
#include "Block.h"
#include "BoardFigure.h"
#include "Spaceship.h"
#include "ObjectId.h"
#include <vector>


class SpaceShip;
class Block;
class Point;

class Board
{
	Point mat[HORIZONTAL_SIZE][VERTICAL_SIZE];
	int maxHorizontalSize = HORIZONTAL_SIZE;
	int maxVerticalSize = VERTICAL_SIZE;
	long timeRemains = MAX_TIME;
	Block* allBlocks[3];
	int blocksAmount = 0;

public:
	Block* getBlockById(int objectId);
	void removeShipFromBoard(SpaceShip ship);
	bool checkExit(SpaceShip ship);
	bool isNotEmptyPoint(int x, int y, int direction, vector<Block*>& blocksInvolve);
	void revertStartUpBoard();
	void initBoard();
	int CheckObjectId(char ch);
	void setTimeRemains(long timeToSet) { timeRemains = timeToSet; };
	long getTimeRemains() { return timeRemains; };
	void timeDown() { timeRemains--; };
	void setMaxHorizontalSize(int _horizontal) { maxHorizontalSize = _horizontal; };
	int getMaxHorizontalSize() { return maxHorizontalSize; };
	void setGetMaxVerticalSize(int _vertical) { maxVerticalSize = _vertical; };
	int getMaxVerticalSize() { return maxVerticalSize; };
	auto getMat() { return mat; };
	void draw();
	auto getAllBlocks();
	void setMatrixPoint(int _x, int _y, Point* _p);
	Board(int _maxHorizontalSize, int _maxVerticalSize, long _timeRemains) {
		maxHorizontalSize = _maxHorizontalSize;
		maxVerticalSize = _maxVerticalSize;
		timeRemains = _timeRemains;
	};
	Board();
	Board(const Board& _board) = default;
	Board& operator=(const Board& _board) = default;
	bool isBlockCanMove(Block* block, int direction);
	void fallBlocksIfNoFloor();


private:
	bool isPointNoFloor(int x, int y, int bulkId);
	void initBlocks();
	void placeBlocksOnBoard();
	void insertNewBlock(Block* block);
	bool isValidPlace(int x, int y, Block* block);
};



