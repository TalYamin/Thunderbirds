#include "Spaceship.h"


SpaceShip::SpaceShip()
{
}

SpaceShip::SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color, Board* _board) {

	verticalSize = _verticalSize;
	horizontalSize = _horizontalSize;
	figure = _figure;
	color = _color;
	board = _board;
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
		mat[0] = new Point(2, 2, figure); //free is needed
		mat[1] = new Point(3, 2, figure); //free is needed

		break;
	case ShipSize::BIG:
		mat[0] = new Point[2]{ {77,2,figure},{78,2,figure} }; //free is needed
		mat[1] = new Point[2]{ {77,3,figure},{78,3,figure} };//free is needed
		break;
	default:
		break;
	}

}

Point** SpaceShip::getMat() {
	return mat;
}


void SpaceShip::move(ShipSize size) {

	switch (size)
	{
	case ShipSize::SMALL:
		checkSmallBlockedWall();
		if (!isBlock){
			moveSmallShip();
		}
		break;
	case ShipSize::BIG:
		moveBigShip();
		break;
	default:
		break;
	}
}

void  SpaceShip::initDraw(ShipSize size) {
	switch (size)
	{
	case ShipSize::SMALL:
		setTextColor(color);
		mat[0]->draw();
		mat[1]->draw();
		break;
	case ShipSize::BIG:
		setTextColor(color);
		mat[0][0].draw();
		mat[0][1].draw();
		mat[1][0].draw();
		mat[1][1].draw();
		break;
	default:
		break;
	}
}

void SpaceShip::moveBigShip() {

	mat[0][0].draw(' ');
	mat[0][1].draw(' ');
	mat[1][0].draw(' ');
	mat[1][1].draw(' ');
	mat[0][0].move(direction);
	mat[0][1].move(direction);
	mat[1][0].move(direction);
	mat[1][1].move(direction);
	setTextColor(color);
	mat[0][0].draw();
	mat[0][1].draw();
	mat[1][0].draw();
	mat[1][1].draw();

}

void SpaceShip::moveSmallShip() {

	mat[0]->draw(' ');
	mat[1]->draw(' ');
	mat[0]->move(direction);
	mat[1]->move(direction);
	setTextColor(color);
	mat[0]->draw();
	mat[1]->draw();

}

void SpaceShip::checkSmallBlockedWall() {

	Point p1, p2;

	switch (direction) {
	case 0: // UP
		p2 = *mat[1];
		p2.setY(p2.getY() - 1);
		if ((board->getMat()[mat[0]->getX()][mat[0]->getY()-1].getFigure() == '+') || (board->getMat()[mat[1]->getX()][mat[1]->getY() - 1].getFigure() == '+')) {
			isBlock = true;
		}
		else {
			isBlock = false;
		}
		break;
	case 1: // DOWN
		if ((board->getMat()[mat[0]->getX()][mat[0]->getY() + 1].getFigure() == '+') || (board->getMat()[mat[1]->getX()][mat[1]->getY() + 1].getFigure() == '+')) {
			isBlock = true;
		}else {
			isBlock = false;
		}
		break;
	case 2: // LEFT
		if ((board->getMat()[mat[0]->getX()-1][mat[0]->getY()].getFigure() == '+')) {
			isBlock = true;
		}
		else {
			isBlock = false;
		}
		break;
	case 3: // RIGHT
		p2 = *mat[1];
		p2.setX(p2.getX() + 1);
		if ((board->getMat()[mat[1]->getX() + 1][mat[1]->getY()].getFigure() == '+')) {
			isBlock = true;
		}
		else {
			isBlock = false;
		}
		break;
	default:
		isBlock = false;
		break;
	}
}





