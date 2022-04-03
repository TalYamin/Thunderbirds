#include "Block.h"


/*
Constructor for Block.
*/
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

/*
Constructor for Block.
*/
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

/*
This if setter function of figure data member.
*/
void Block::setFigure(char fig) {
	figure = fig;
}

/*
This if setter function of is block data member.
*/
void Block::setIsBlock()
{
	isBlock == true ? isBlock = false : isBlock = true;
};


/*
This if setter function of color data member.
*/
void Block::setColor(Color c)
{
	color = c;
}

/*
This if getter function of size data member.
*/
int Block::getSize () const{
	return size;
}
/*
This if getter function of list points data member.
*/
Point** Block::getListPoints() const{
	return list_points;
}

/*
This function draw blocks.
*/
void Block::drawBlock() const {
	for (int i = 0; i < size; i++)
	{
		list_points[i]->draw();
	}
}

/*
This if getter function of block id data member.
*/
int Block::getblockId() const {
	return blockId;
}

/*
Distructor of Block
*/
Block::~Block()
{
}

/*
This function is used to move.
First, function clean the previous location of block. Remove figures from board and update
board matrix. Then, function draws block figure on board in new location and update board matrix.
*/
void Block::move(int direction, Board* board)
{
	for (int i = 0; i < size; i++) {
		list_points[i]->draw((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setObjecId((int)ObjectId::EMPTY);
	}

	for (int i = 0; i < size; i++) {
		list_points[i]->move(direction);
		list_points[i]->draw();
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure(figure);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setObjecId(blockId);
	}
}

/*
This function is used to make block falling.
*/
void Block::fall(Board* board)
{
	move(1, board);
}