#pragma once
#include "Point.h"
#include "Color.h"
#include "Board.h"

class Block
{
	Point** list_points;
	char figure = 'B';
	Color color = Color::RED;
	bool isShipBlock = false;
	int size = 0;
public:
	~Block();
	Block(Point** _list_points, char _figure, Color _color, bool _isBlock, int _size);
	Block(Point** _list_points, int size);
	Block() = default;

	void move(Board* board, int direction);
	void setFigure(char fig);
	void setIsBlock();
	void setColor(Color c);
	int getSize();
	Point** getListPoints();
	void drawBlock();


private:
	int calculateSize();
	void fall();
};



