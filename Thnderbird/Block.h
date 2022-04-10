#pragma once
#include "Point.h"
#include "Color.h"
#include "Board.h"

class Board;

class Block
{
	//data members
	Point** list_points;
	char figure = 'B';
	Color color = Color::RED;
	bool isBlock = false;
	int size = 0;
	int blockId = (int)ObjectId::EMPTY;
	static int idGenerator;


public:

	//ctors + dtros
	Block() = default;
	Block(Point** _list_points, int size);
	Block(Point** _list_points, char _figure, Color _color, bool _isBlock, int _size, int _blockId);
	Block(const Block& _block) = default;
	Block& operator=(const Block& _block) = default;
	~Block();


	//getters + setters
	void move(int direction, Board* board);
	void setFigure(char fig);
	void setIsBlock();
	void setColor(Color c);
	int getSize () const;
	Point** getListPoints () const;
	
	//public methods
	void drawBlock() const;
	int getblockId () const;
	void fall(Board* board);

private:
	
};



