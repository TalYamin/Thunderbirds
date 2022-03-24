#include "Block.h"


Block::Block(Point* _list_points, char _figure, Color _color, bool _isBlock, int _size) {
	for (int i = 0; i < size; i++)
	{
		list_points[i] = _list_points[i];
	}
	figure = _figure;
	color = _color;
	isBlock = _isBlock;
	size = _size;
};

Block::~Block()
{
}