#pragma once
#define HORIZONTAL_SIZE 80
#define VERTICAL_SIZE 25
#include "Point.h";
#include "Time.h";

class Board
{
	Point* mat[HORIZONTAL_SIZE] = { 0 };
	int maxHorizontalSize;
	int maxVerticalSize;
	Time timeRemains;
public:
	void revertStartUpBoard();
	Point** initBoard();
	void setTimeRemains(long timeToSet)
	{
		timeRemains = timeToSet;
	};
	Time getTimeRemains() {
		return timeRemains;
	};
	void setMaxHorizontalSize(int _horizontal) { maxHorizontalSize = _horizontal; };
	int getMaxHorizontalSize() { return maxHorizontalSize; };
	void setGetMaxVerticalSize(int _vertical) { maxVerticalSize = _vertical; };
	int getMaxVerticalSize() { return maxVerticalSize; };
	void draw();
	Board(int _maxHorizontalSize, int _maxVerticalSize, Time _timeRemains) {
		maxHorizontalSize = _maxHorizontalSize;
		maxVerticalSize = _maxVerticalSize;
		timeRemains = _timeRemains;
	};


private:

};



