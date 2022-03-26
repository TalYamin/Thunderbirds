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


void SpaceShip::move(ShipSize size, Board* board) {

	switch (size)
	{
	case ShipSize::SMALL:
		checkSmalldWallCollision(board);
		if (!isBlock) {
			moveSmallShip(board);
		}
		break;
	case ShipSize::BIG:
		checkSBigdWallCollision(board);
		if (!isBlock) {
			moveBigShip(board);
		}
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

void SpaceShip::moveBigShip(Board* board) {

	for (int i = 0; i < BIG_HORIZONTAL_SIZE; i++)
	{
		for (int j = 0; j < BIG_VERTICAL_SIZE; j++){
			mat[i][j].draw((char)BoardFigure::EMPTY);
			board->getMat()[mat[i][j].getX()][mat[i][j].getY()].setFigure((char)BoardFigure::EMPTY);
			mat[i][j].move(direction);
			board->setMatrixPoint(mat[i][j].getX(), mat[i][j].getY(), mat[i]);
		}
	}

	setTextColor(color);
	for (int i = 0; i < BIG_HORIZONTAL_SIZE; i++)
	{
		for (int j = 0; j < BIG_VERTICAL_SIZE; j++) {
			mat[i][j].draw();
		}
	}
	
}

void SpaceShip::moveSmallShip(Board* board) {

	for (int i = 0; i < SMALL_HORIZONTAL_SIZE; i++){
		mat[i]->draw((char)BoardFigure::EMPTY);
		board->getMat()[mat[i]->getX()][mat[i]->getY()].setFigure((char)BoardFigure::EMPTY);
		mat[i]->move(direction);
		board->setMatrixPoint(mat[i]->getX(), mat[i]->getY(), mat[i]);
	}

	setTextColor(color);
	for (int i = 0; i < SMALL_HORIZONTAL_SIZE; i++) {
		mat[i]->draw();
	}

}

void SpaceShip::checkSBigdWallCollision(Board* board) {

	switch (direction) {
	case 0: // UP
		isBlock = (board->isNotEmptyPoint(mat[0][0].getX(), mat[0][0].getY() - 1)) || (board->isNotEmptyPoint(mat[0][1].getX(), mat[0][1].getY() - 1));
		break;
	case 1: // DOWN
		isBlock = (board->isNotEmptyPoint(mat[1][0].getX(), mat[1][0].getY() + 1)) || (board->isNotEmptyPoint(mat[1][1].getX(), mat[1][1].getY() + 1));
		break;
	case 2: // LEFT
		isBlock = (board->isNotEmptyPoint(mat[0][0].getX() - 1, mat[0][0].getY())) || (board->isNotEmptyPoint(mat[1][0].getX() - 1, mat[1][0].getY()));
		break;
	case 3: // RIGHT
		isBlock = (board->isNotEmptyPoint(mat[0][1].getX() + 1, mat[0][1].getY())) || (board->isNotEmptyPoint(mat[1][1].getX() + 1, mat[1][1].getY()));
		break;
	default:
		isBlock = false;
		break;
	}
}



void SpaceShip::checkSmalldWallCollision(Board* board) {
	switch (direction) {
	case 0: // UP
		isBlock = (board->isNotEmptyPoint(mat[0]->getX(), mat[0]->getY() - 1)) || (board->isNotEmptyPoint(mat[1]->getX(), mat[1]->getY() - 1));
		break;
	case 1: // DOWN
		isBlock = (board->isNotEmptyPoint(mat[0]->getX(), mat[0]->getY() + 1)) || (board->isNotEmptyPoint(mat[1]->getX(), mat[1]->getY() + 1));
		break;
	case 2: // LEFT
		isBlock = board->isNotEmptyPoint(mat[0]->getX() - 1, mat[0]->getY());
		break;
	case 3: // RIGHT
		isBlock = board->isNotEmptyPoint(mat[1]->getX() + 1, mat[1]->getY());
		break;
	default:
		isBlock = false;
		break;
	}
}





