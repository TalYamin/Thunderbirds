#include "Ghost.h"

Ghost::Ghost(Point* _point, int _ghostId)
{

	point = _point;
	ghostId = _ghostId;

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
