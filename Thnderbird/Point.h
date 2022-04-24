#pragma once

#include <iostream>
#include "io_utils.h"
#include "ObjectId.h"
#include "BoardFigure.h"
#include "Direction.h"
#define HORIZONTAL_SIZE 80
#define VERTICAL_SIZE 25

using namespace std;


class Point
{
	//data members
	int objectId = (int)ObjectId::EMPTY;
	int x = 1;
	int y = 1;
	char figure = (char)BoardFigure::EMPTY;
	Color color = Color::WHITE;

public:

	//ctors + dtors
	Point(int _x, int _y);
	Point(int _x, int _y, char _fig);
	Point(int _x, int _y, char _fig, Color _color);
	Point(int _x, int _y, char _fig, Color _color, int _objectId);
	Point() = default;
	Point(const Point& _p) = default;
	Point& operator=(const Point& _p) = default;
	~Point();


	//getters + setters
	void setX(int _x);
	void setY(int _y);
	int getX() const;
	int getY() const;
	void setObjecId(int _objectId);
	int getObjecId() const;
	char getFigure() const;
	void setFigure(char _figure);

	//public methods
	void draw() const;
	void draw(char _fig);
	void move(int direction);

private:

};


