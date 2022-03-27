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
	list_points = (Point**)malloc(sizeof(Point*) * size);
	for (int i = 0; i < size; i++)
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

void Block::initBlock()
{
	int firstBlockSize = 1;
	int secondBlockSize = 4;
	int thiredBlockSize = 3;

	Point* block1Point1 = new Point(5, 2, figure);

	Point* blockList1[] = { block1Point1 };
	Block* block1 = new Block(blockList1, firstBlockSize);

	Point* block2Point1 = new Point(35, 9, figure);
	Point* block2Point2 = new Point(36, 9, figure);
	Point* block2Point3 = new Point(35, 10, figure);
	Point* block2Point4 = new Point(36, 10, figure);

	Point* blockList2[] = { block2Point1,block2Point2,block2Point3,block2Point4 };
	Block* block2 = new Block(blockList2, secondBlockSize);

	Point* block3Point1 = new Point(55, 19, figure);
	Point* block3Point2 = new Point(56, 19, figure);
	Point* block3Point3 = new Point(57, 19, figure);

	Point* blockList3[] = { block3Point1,block3Point2,block3Point3 };
	Block* block1 = new Block(blockList3, thiredBlockSize);

}
