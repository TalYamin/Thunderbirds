#include "Ghost.h"

int Ghost::idGenerator = 1000;

Ghost::Ghost(Point* _point)
{

	point = _point;
	point->setFigure(figure);
	point->setColor(color);
	point->setObjecId(idGenerator++);

}

Ghost::Ghost(Point* _point, char _figure, Color _color, bool _isBlock, int _ghostId)
{

	point = _point;
	figure = _figure;
	color = _color;
	isBlock = _isBlock;
	ghostId = _ghostId;
}

Ghost::~Ghost()
{
}
