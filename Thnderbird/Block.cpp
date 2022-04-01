#include "Block.h"


Block::Block(Point** _list_points, char _figure, Color _color, bool _isBlock, int _size, int _blockId) {
	list_points = (Point**)malloc(sizeof(Point*) * size);
	for (int i = 0; i < size; i++)
	{
		list_points[i] = _list_points[i];
	}
	figure = _figure;
	color = _color;
	isBlock = _isBlock;
	size = _size;
	blockId = _blockId;
}
Block::Block(Point** _list_points, int _size, int _blockId)
{
	list_points = (Point**)malloc(sizeof(Point*) * _size);
	for (int i = 0; i < _size; i++)
	{
		list_points[i] = _list_points[i];
	}
	size = _size;
	blockId = _blockId;
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

int Block::getSize () const{
	return size;
}

Point** Block::getListPoints() const{
	return list_points;
}

void Block::drawBlock() const {
	for (int i = 0; i < size; i++)
	{
		list_points[i]->draw();
	}
}

int Block::getblockId() const {
	return blockId;
}


Block::~Block()
{
}

void Block::move(int direction, Board* board)
{
	for (int i = 0; i < size; i++) {
		list_points[i]->draw((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure((char)BoardFigure::EMPTY);
	}

	for (int i = 0; i < size; i++) {
		list_points[i]->move(direction);
		list_points[i]->draw();
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure(figure);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setObjecId(blockId);
	}
}

void Block::fall(Board* board)
{
	move(1, board);
}