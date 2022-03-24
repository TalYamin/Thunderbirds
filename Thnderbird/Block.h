#pragma once
#include "Point.h"
#include "Color.h"

class Block
{
	Point* list_points;
	char figure = 'B';
	Color color;
	bool isBlock;
	int size;
public:
	~Block();
	Block(Point* _list_points, char _figure, Color _color, bool _isBlock, int _size);
	void move();
	void setFigure(char fig) { figure = fig; };
	void setIsBlock() {
		isBlock == true ? isBlock = false : isBlock = true;
	};
	void setColor(Color c) {
		color = c;
	};
	void setSize() { sizeof(Point) / sizeof(list_points[0]); };
private:
	void fall();
};



