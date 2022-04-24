#include "Point.h"

/*
Constructor of Point with 2 parameters.
*/
Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
};

/*
Constructor of Point with 3 parameters.
*/
Point::Point(int _x, int _y, char _fig)
{
	x = _x;
	y = _y;
	figure = _fig;
}

/*
Constructor of Point with 4 parameters.
*/
Point::Point(int _x, int _y, char _fig, Color _color)
{
	x = _x;
	y = _y;
	figure = _fig;
	color = _color;
}
/*
Constructor of Point with 5 parameters.
*/
Point::Point(int _x, int _y, char _fig, Color _color, int _objectId)
{
	x = _x;
	y = _y;
	figure = _fig;
	color = _color;
	objectId = _objectId;
}


/*
This is setter function of x data member.
*/
void Point::setX(int _x) {
	x = _x;

}

/*
This is setter function of y data member.
*/
void Point::setY(int _y) {
	y = _y;
}

/*
This is getter function of x data member.
*/
int Point::getX() const
{
	return x;
}

/*
This is getter function of y data member.
*/
int Point::getY() const
{
	return y;
}

/*
This function is used to make point movement according to direction.
*/
void Point::move(int dir) {
	switch (dir) {
	case (int)Direction::UP:
		--y;
		break;
	case (int)Direction::DOWN:
		++y;
		break;
	case (int)Direction::LEFT:
		--x;
		break;
	case (int)Direction::RIGHT:
		++x;
		break;
	}
}

/*
This is getter function of figure data member.
*/
char Point::getFigure() const
{
	return figure;
}

/*
This function is used to draw point.
*/
void Point::draw() const {
	if (x < HORIZONTAL_SIZE && y < VERTICAL_SIZE)
	{
		gotoxy(x, y);
		setTextColor(color);
		cout << figure;
	}
}

/*
This function is used to dreaw point with figure parameter.
*/
void Point::draw(char _fig)
{
	if (x < HORIZONTAL_SIZE && y < VERTICAL_SIZE)
	{
		gotoxy(x, y);
		cout << _fig;
	}
}

/*
This is setter function of figure data member.
*/
void  Point::setFigure(char _figure) {
	figure = _figure;
}


/*
This is setter function of object id data member.
*/
void Point::setObjecId(int _objectId) {
	objectId = _objectId;
}

/*
This is getter function of object id data member.
*/
int Point::getObjecId() const {
	return objectId;
}

/*
Distructor of Point.
*/
Point::~Point() {

}