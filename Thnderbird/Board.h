#pragma once
#define HORIZONTAL_SIZE 80
#define VERTICAL_SIZE 25
#include "Point.h"
#define TIME_X 30
#define TIME_Y 30
#define LIVES_X 30
#define LIVES_Y 29

class Board
{
	Point mat[HORIZONTAL_SIZE][VERTICAL_SIZE] = { {} };
	int maxHorizontalSize = HORIZONTAL_SIZE;
	int maxVerticalSize = VERTICAL_SIZE;
	long timeRemains = 10000;

public:
	void revertStartUpBoard();
	void initBoard();
	void setTimeRemains(long timeToSet) { timeRemains = timeToSet; };
	long getTimeRemains() { return timeRemains; };
	void timeDown() { timeRemains--; };
	void setMaxHorizontalSize(int _horizontal) { maxHorizontalSize = _horizontal; };
	int getMaxHorizontalSize() { return maxHorizontalSize; };
	void setGetMaxVerticalSize(int _vertical) { maxVerticalSize = _vertical; };
	int getMaxVerticalSize() { return maxVerticalSize; };
	void draw();
	void setMatrixPoint(int _x, int _y, Point* _p);
	Board(int _maxHorizontalSize, int _maxVerticalSize, long _timeRemains) {
		maxHorizontalSize = _maxHorizontalSize;
		maxVerticalSize = _maxVerticalSize;
		timeRemains = _timeRemains;
	};
	Board() {};
	Board(const Board& _board) = default;
	Board& operator=(const Board& _board) = default;

private:

};



