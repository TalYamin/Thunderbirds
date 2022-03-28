#include "Block.h"


Block::Block(Point** _list_points, char _figure, Color _color, bool _isBlock, int _size) {
	list_points = (Point**)malloc(sizeof(Point*) * size);
	for (int i = 0; i < size; i++)
	{
		list_points[i] = _list_points[i];
	}
	figure = _figure;
	color = _color;
	isBlock = _isBlock;
	size = _size;
}
Block::Block(Point** _list_points, int _size)
{
	list_points = (Point**)malloc(sizeof(Point*) * _size);
	for (int i = 0; i < _size; i++)
	{
		list_points[i] = _list_points[i];
	}
	size = _size;
}


void Block::setFigure(char fig) {
	figure = fig;
}

void Block::setIsBlock()
{
	isBlock == true ? isBlock = false : isBlock = true;
};

void Block::setColor(Color c)
{
	color = c;
}

int Block::getSize()
{
	return size;
}

Point** Block::getListPoints()
{
	return list_points;
}

void Block::drawBlock()
{
	setTextColor(Color::RED);
	for (int i = 0;i < size;i++)
	{
		list_points[i]->draw();
	}
}


Block::~Block()
{
}

