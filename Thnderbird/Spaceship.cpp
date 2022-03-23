#include "Spaceship.h"

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
	return key; 
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
		mat[0] = new Point; //free is needed
		mat[1] = new Point; //free is needed

		break;
	case ShipSize::BIG:
		mat[0] = new Point[2]; //free is needed
		mat[1] = new Point[2]; //free is needed
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
		break;
	case ShipSize::BIG:
		break;
	default:
		break;
	}
}


void SpaceShip::moveSmallShip() {

}






SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}
