#include "HorizontalGhost.h"

HorizontalGhost::HorizontalGhost(char _figure, vector <Point*> _list_points, int _size) : LineGhost(_list_points, _size)
{
	figure = _figure;
}

HorizontalGhost::~HorizontalGhost()
{
}

char HorizontalGhost::getFigure()
{
	return figure;
}

int HorizontalGhost::getDirection()
{
	return direction;
}

void HorizontalGhost::switchDirection()
{

	direction = direction == (int)Direction::RIGHT ? (int)Direction::LEFT : (int)Direction::RIGHT;

}
