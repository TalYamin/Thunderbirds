#pragma once

#include "Point.h"
#include "Board.h"
#include "Direction.h"
#define START_GHOST_ID 1000

class Point;

class Ghost
{

	//data members
	vector <Point*> list_points;
	Color color = Color::BROWN;
	bool isGhostBlock = false;
	int ghostId = (int)ObjectId::EMPTY;
	static int idGenerator;
	int size = 0;
	bool isGhostHit = false;

public:
	//ctors + dtors
	Ghost() = default;
	Ghost(vector <Point*> _list_points, int _size);
	Ghost(vector <Point*> _list_points, Color _color, bool _isGhostBlock, int _ghostId);
	Ghost(const Ghost& _ghost) = default;
	Ghost& operator=(const Ghost& _ghost) = default;
	virtual ~Ghost();


	//getters + setters
	int getSize();
	int getId();
	vector<Point*> getListPoints();
	bool getIsGhostBlock();
	bool getIsGhostHit();
	void setIsGhostBlock(bool _isGhostBlock);
	void setIsGhostHit(bool _isGhostHit);
	
	//virtual methods
	virtual void Move(Board* board) = 0;
	virtual char getFigure() = 0;
	virtual int getDirection() = 0;
	virtual void switchDirection() = 0;
	virtual void checkGhostCollision(Board* board) = 0;

	//public methods
	void MoveGhost(Board* board);
	bool isGhostHitShip(Board* board, int x, int y);

private:

};
