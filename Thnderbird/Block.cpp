#include "Block.h"


Block::Block(Point** _list_points, char _figure, Color _color, bool _isBlock, int _size) {
	list_points = (Point**)malloc(sizeof(Point*) * size);
	for (int i = 0; i < size; i++)
	{
		list_points[i] = _list_points[i];
	}
	figure = _figure;
	color = _color;
	isShipBlock = _isBlock;
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


void Block::move(Board* board, int direction)
{

	for (int i = 0; size; i++) {

		list_points[i]->draw((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure((char)BoardFigure::EMPTY);
	}

	for (int i = 0; i < size; i++) {
		list_points[i]->move(direction);
		list_points[i]->draw();
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure(figure);
	}

}

void Block::setFigure(char fig) {
	figure = fig;
}

void Block::setIsBlock()
{
	isShipBlock == true ? isShipBlock = false : isShipBlock = true;
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
	for (int i = 0;i < size;i++)
	{
		list_points[i]->draw();
	}
}


Block::~Block()
{
}

