#pragma once

class Point
{
	int x = 1;
	int y = 1;
public:
	void draw(char ch);
	void move(int direction);
	Point() {};
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	};
	~Point();
private:

};

Point::~Point()
{
}