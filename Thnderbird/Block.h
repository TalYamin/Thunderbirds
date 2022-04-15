#pragma once
#include "Point.h"
#include "Color.h"
#include "Board.h"
#include <vector>

class Board;

class Block
{
	//data members
	vector <Point*> list_points;
	char figure;
	Color color = Color::RED;
	bool isBlock = false;
	int blockId = (int)ObjectId::EMPTY;
	static int idGenerator;


public:

	//ctors + dtros
	Block() = default;
	Block(vector <Point*> _list_points, char _figure);
	Block(vector <Point*> _list_points, char _figure, Color _color, bool _isBlock, int _blockId);
	Block(const Block& _block) = default;
	Block& operator=(const Block& _block) = default;
	~Block();


	//getters + setters
	void move(int direction, Board* board);
	void setFigure(char fig);
	void setIsBlock();
	void setColor(Color c);
	vector<Point*> getListPoints();
	
	//public methods
	void drawBlock() const;
	int getblockId () const;
	void fall(Board* board);
	void addPointToBlock(Point* p);

private:
	
};



