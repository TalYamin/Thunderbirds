#pragma once
#define HORIZONTAL_SIZE 80
#define VERTICAL_SIZE 25
#include "Point.h"
#include "Time.h"
#include "Spaceship.h"

class Spaceship;

class Board
{
	Point mat[HORIZONTAL_SIZE][VERTICAL_SIZE] = { {} };
	int maxHorizontalSize = HORIZONTAL_SIZE;
	int maxVerticalSize = VERTICAL_SIZE;
	Time timeRemains = { 100000 };
public:
	void revertStartUpBoard();
	void initBoard();
	void setTimeRemains(long timeToSet) { timeRemains = timeToSet; };
	Time getTimeRemains() { return timeRemains; };
	void setMaxHorizontalSize(int _horizontal) { maxHorizontalSize = _horizontal; };
	int getMaxHorizontalSize() { return maxHorizontalSize; };
	void setGetMaxVerticalSize(int _vertical) { maxVerticalSize = _vertical; };
	int getMaxVerticalSize() { return maxVerticalSize; };
	Point (*getMat())[VERTICAL_SIZE] {return mat; };
	void draw();
	void setMatrixPoint(int _x, int _y, Point* _p);
	Board(int _maxHorizontalSize, int _maxVerticalSize, Time _timeRemains) {
		maxHorizontalSize = _maxHorizontalSize;
		maxVerticalSize = _maxVerticalSize;
		timeRemains = _timeRemains;
	};
	Board() {};
	Board(const Board& _board) = default;
	Board& operator=(const Board& _board) = default;

private:

};



