#include "Spaceship.h"


SpaceShip::SpaceShip()
{
}

SpaceShip::SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color) {
	
	verticalSize = _verticalSize;
	horizontalSize = _horizontalSize;
	figure = _figure;
	color = _color;
	
}

SpaceShip::~SpaceShip()
{
}


void SpaceShip::setType(int typeNum) {
	type = static_cast<ShipSize>(typeNum);
}

SpaceShip::ShipSize SpaceShip::getType() {
	return type;
}

void SpaceShip::setVerticalSize(int _verticalSize) {
	verticalSize = _verticalSize;
}

int SpaceShip::getVerticalSize() {
	return verticalSize;
}

void SpaceShip::setHorizontalSize(int _horizontalSize) {
	horizontalSize = _horizontalSize;
}


int SpaceShip::getHorizontalSize() {
	return horizontalSize;
}

void SpaceShip::setDirection(int _direction) {
	direction = _direction;
}

int SpaceShip::getDirection(char key) {
	for (int i = 0; i < 4; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

void SpaceShip::setFigure(const char c) {
	figure = c;
}

char SpaceShip::getFigure() {
	return figure;
}


void SpaceShip::setArrowKeys(const char* keys) { // "wzad"
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
};


void SpaceShip::setColor(Color _color) {
	color = _color;
}

Color SpaceShip::getColor() {
	return color;
}


void SpaceShip::setIsBlock() {
	isBlock == true ? isBlock = false : isBlock = true;
};

bool SpaceShip::getIsBlock() {
	return isBlock;
}

void SpaceShip::setMat(ShipSize size) {

	switch (size)
	{
	case ShipSize::SMALL:
		mat[0] = new Point(3,3); //free is needed
		mat[1] = new Point(3,4); //free is needed

		break;
	case ShipSize::BIG:
		mat[0] = new Point[2]; //free is needed
		mat[0][0].setX(3);
		mat[0][0].setY(77);
		mat[0][1].setX(3);
		mat[0][1].setY(78);
		mat[1] = new Point[2]; //free is needed
		mat[1][0].setX(4);
		mat[1][0].setY(77);
		mat[1][1].setX(4);
		mat[1][1].setY(78);
		break;
	default:
		break;
	}

}

Point** SpaceShip::getMat() {
	return mat;
}


void SpaceShip::move(ShipSize size){

	switch (size)
	{
	case ShipSize::SMALL:
		moveSmallShip();
		break;
	case ShipSize::BIG:
		break;
	default:
		break;
	}
}


void SpaceShip::moveSmallShip() {
	
	mat[0]->draw();
	mat[1]->draw();
	mat[1]->move(direction);
	mat[0]->move(direction);
	setTextColor(color);
	mat[1]->draw();

}




