#include "Point.h"


Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;

};

Point::Point(int _x, int _y, char _fig)
{
	x = _x;
	y = _y;
	figure = _fig;
};

void Point::setX(int _x) {
	x = _x;

}
void Point::setY(int _y) {
	y = _y;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

void Point::move(int dir) {
	switch (dir) {
	case 0: // UP
		--y;
		break;
	case 1: // DOWN
		++y;
		break;
	case 2: // LEFT
		--x;
		break;
	case 3: // RIGHT
		++x;
		break;
	}
}

char Point::getFigure()
{
	return figure;
}

void Point::draw() {
	gotoxy(x, y);
	cout << figure << endl;
}