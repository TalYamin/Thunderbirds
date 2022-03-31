#pragma once
#include "Point.h"
#include "Color.h"
#include "Board.h"

class Block
{
	Point** list_points;
	char figure = 'B';
	Color color = Color::RED;
	bool isBlock = false;
	int size = 0;
	int blockId = (int)ObjectId::EMPTY;

public:
	~Block();
	Block(Point** _list_points, char _figure, Color _color, bool _isBlock, int _size, int _blockId);
	Block(Point** _list_points, int size, int _blockId);
	Block() = default;
	void setFigure(char fig);
	void setIsBlock();
	void setColor(Color c);
	int getSize () const;
	Point** getListPoints () const;
	void drawBlock() const;
	int getblockId () const;


private:
	int calculateSize();
	void fall();
};



