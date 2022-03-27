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

ShipSize SpaceShip::getType() {
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
	for (int i = 0; i < NUM_ARROW_KEYS; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return NO_DIRECTION;
}

void SpaceShip::setFigure(const char c) {
	figure = c;
}

char SpaceShip::getFigure() {
	return figure;
}


void SpaceShip::setArrowKeys(const char* keys) { // "wzad"
	for (int i = 0; i < NUM_ARROW_KEYS; i++)
	{
		arrowKeys[i] = keys[i];
	}
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

void SpaceShip::setShipMat(Board* board) {

	switch (type)
	{
	case ShipSize::SMALL:
		shipMat[0] = new Point(2, 2, figure); //free is needed
		shipMat[1] = new Point(3, 2, figure); //free is needed
		board->setMatrixPoint(shipMat[0]->getX(), shipMat[0]->getY(), shipMat[0]);
		board->setMatrixPoint(shipMat[1]->getX(), shipMat[1]->getY(), shipMat[1]);
		break;
	case ShipSize::BIG:
		shipMat[0] = new Point[2]{ {77,2,figure},{78,2,figure} }; //free is needed
		shipMat[1] = new Point[2]{ {77,3,figure},{78,3,figure} };//free is needed
		for (int i = 0; i < verticalSize; i++)
		{
			for (int j = 0; j < horizontalSize; j++) {
				board->setMatrixPoint(shipMat[i][j].getX(), shipMat[i][j].getY(), &shipMat[i][j]);
			}
		}
		break;
	default:
		break;
	}

}

auto SpaceShip::getShipMat() {
	return shipMat;
}


void SpaceShip::move(Board* board) {

	switch (type)
	{
	case ShipSize::SMALL:
		checkSmallCollision(board);
		if (!isBlock) {
			moveSmallShip(board);
		}
		break;
	case ShipSize::BIG:
		checkSBigCollision(board);
		if (!isBlock) {
			moveBigShip(board);
		}
		break;
	default:
		break;
	}
}

void  SpaceShip::initDraw() {
	switch (type)
	{
	case ShipSize::SMALL:
		setTextColor(color);
		for (int i = 0; i < horizontalSize; i++){
			shipMat[i]->draw();
		}
		break;
	case ShipSize::BIG:
		setTextColor(color);
		for (int i = 0; i < verticalSize; i++){
			for (int j = 0; j < horizontalSize; j++) {
				shipMat[i][j].draw();
			}
		}
		break;
	default:
		break;
	}
}

void SpaceShip::moveBigShip(Board* board) {


	for (int i = 0; i < verticalSize; i++)
	{

		for (int j = 0; j < horizontalSize; j++) {
			shipMat[i][j].draw((char)BoardFigure::EMPTY);
			board->getMat()[shipMat[i][j].getX()][shipMat[i][j].getY()].setFigure((char)BoardFigure::EMPTY);
		}
	}


	setTextColor(color);
	for (int i = 0; i < verticalSize; i++)
	{
		for (int j = 0; j < horizontalSize; j++) {
			shipMat[i][j].move(direction);
			shipMat[i][j].draw();
			board->getMat()[shipMat[i][j].getX()][shipMat[i][j].getY()].setFigure(figure);
		}
	}

}

void SpaceShip::moveSmallShip(Board* board) {

	for (int i = 0; i < horizontalSize; i++){
		shipMat[i]->draw((char)BoardFigure::EMPTY);
		board->getMat()[shipMat[i]->getX()][shipMat[i]->getY()].setFigure((char)BoardFigure::EMPTY);
	}

	setTextColor(color);
	for (int i = 0; i < horizontalSize; i++) {
		shipMat[i]->move(direction);
		shipMat[i]->draw();
		board->getMat()[shipMat[i]->getX()][shipMat[i]->getY()].setFigure(figure);
	}

}

void SpaceShip::checkSBigCollision(Board* board) {

	switch (direction) {
	case 0: // UP
		isBlock = (board->isNotEmptyPoint(shipMat[0][0].getX(), shipMat[0][0].getY() - 1)) || (board->isNotEmptyPoint(shipMat[0][1].getX(), shipMat[0][1].getY() - 1));
		break;
	case 1: // DOWN
		isBlock = (board->isNotEmptyPoint(shipMat[1][0].getX(), shipMat[1][0].getY() + 1)) || (board->isNotEmptyPoint(shipMat[1][1].getX(), shipMat[1][1].getY() + 1));
		break;
	case 2: // LEFT
		isBlock = (board->isNotEmptyPoint(shipMat[0][0].getX() - 1, shipMat[0][0].getY())) || (board->isNotEmptyPoint(shipMat[1][0].getX() - 1, shipMat[1][0].getY()));
		break;
	case 3: // RIGHT
		isBlock = (board->isNotEmptyPoint(shipMat[0][1].getX() + 1, shipMat[0][1].getY())) || (board->isNotEmptyPoint(shipMat[1][1].getX() + 1, shipMat[1][1].getY()));
		break;
	default:
		isBlock = false;
		break;
	}
}



void SpaceShip::checkSmallCollision(Board* board) {
	switch (direction) {
	case 0: // UP
		isBlock = (board->isNotEmptyPoint(shipMat[0]->getX(), shipMat[0]->getY() - 1)) || (board->isNotEmptyPoint(shipMat[1]->getX(), shipMat[1]->getY() - 1));
		break;
	case 1: // DOWN
		isBlock = (board->isNotEmptyPoint(shipMat[0]->getX(), shipMat[0]->getY() + 1)) || (board->isNotEmptyPoint(shipMat[1]->getX(), shipMat[1]->getY() + 1));
		break;
	case 2: // LEFT
		isBlock = board->isNotEmptyPoint(shipMat[0]->getX() - 1, shipMat[0]->getY());
		break;
	case 3: // RIGHT
		isBlock = board->isNotEmptyPoint(shipMat[1]->getX() + 1, shipMat[1]->getY());
		break;
	default:
		isBlock = false;
		break;
	}
}





