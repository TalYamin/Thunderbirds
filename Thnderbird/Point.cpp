#include "Point.h"


Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;

};

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

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}