#pragma once

#include "Point.h"
#include "Board.h"
#include "Direction.h"
#define START_GHOST_ID 1000

class Point;

class Ghost
{
public:

	//data members
	vector <Point*> list_points;
	char figure = (char)BoardFigure::HORIZONTAL_GHOST;
	Color color = Color::BROWN;
	bool isGhostBlock = false;
	int ghostId = (int)ObjectId::EMPTY;
	static int idGenerator;
	int direction = (int)Direction::RIGHT;
	int size = 0;
	bool isGhostHit = false;

	//ctors + dtors
	Ghost() = default;
	Ghost(vector <Point*> _list_points, int _size);
	Ghost(vector <Point*> _list_points, char _figure, Color _color, bool _isGhostBlock, int _ghostId);
	Ghost(const Ghost& _ghost) = default;
	Ghost& operator=(const Ghost& _ghost) = default;
	~Ghost();


	//public methods
	void Move(Board* board);
	int getSize();
	int getId();
	vector<Point*> getListPoints();	
	void setFigure(char _figure);

private:

	//private methods
	void MoveGhost(Board* board);
	void checkGhostCollision(Board* board);
	void switchDirection();
	bool isGhostHitShip(Board* board, int x, int y);
};
