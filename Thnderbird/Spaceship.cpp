#include "Spaceship.h"



SpaceShip::SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color, int _maxCarringBlockSize, ShipSize _type) {

	verticalSize = _verticalSize;
	horizontalSize = _horizontalSize;
	figure = _figure;
	color = _color;
	maxCarringBlockSize = _maxCarringBlockSize;
	type = _type;
}

SpaceShip::~SpaceShip()
{
}


void SpaceShip::setType(int typeNum) {
	type = static_cast<ShipSize>(typeNum);
}

ShipSize SpaceShip::getType() const {
	return type;
}

void SpaceShip::setVerticalSize(int _verticalSize) {
	verticalSize = _verticalSize;
}

int SpaceShip::getVerticalSize() const {
	return verticalSize;
}

void SpaceShip::setHorizontalSize(int _horizontalSize) {
	horizontalSize = _horizontalSize;
}


int SpaceShip::getHorizontalSize() const {
	return horizontalSize;
}

void SpaceShip::setDirection(int _direction) {
	direction = _direction;
}

int SpaceShip::getDirection(char key) const {
	for (int i = 0; i < NUM_ARROW_KEYS; i++)
	{
		if (key == tolower(arrowKeys[i]) || key == toupper(arrowKeys[i]))
			return i;
	}
	return NO_DIRECTION;
}

void SpaceShip::setFigure(const char c) {
	figure = c;
}

char SpaceShip::getFigure() const {
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

Color SpaceShip::getColor() const {
	return color;
}


void SpaceShip::setIsShipBlock() {
	isShipBlock == true ? isShipBlock = false : isShipBlock = true;
};

bool SpaceShip::getIsShipBlock() const {
	return isShipBlock;
}

int SpaceShip::getMaxCarringBlockSize()
{
	return maxCarringBlockSize;
}

void SpaceShip::setMaxCarringBlockSize(int _maxCarringBlockSize)
{
	maxCarringBlockSize = _maxCarringBlockSize;
}

void SpaceShip::setIsExit(bool _isExit) {
	isExit = _isExit;
};

bool SpaceShip::getIsExit() const {
	return isExit;
}

void SpaceShip::setIsDie(bool _isDie) {
	isDie = _isDie;
};

bool SpaceShip::getIsDie() const {
	return isDie;
}

void SpaceShip::setupShipMat(ShipSize type) {

	switch (type)
	{
	case ShipSize::SMALL:
		shipMat[0] = new Point[2]{ {2,2,figure,color,(int)ObjectId::SMALL},{3,2,figure,color,(int)ObjectId::SMALL} }; //free is needed
		break;
	case ShipSize::BIG:
		shipMat[0] = new Point[2]{ {77,2,figure,color,(int)ObjectId::BIG},{78,2,figure,color,(int)ObjectId::BIG} }; //free is needed
		shipMat[1] = new Point[2]{ {77,3,figure,color,(int)ObjectId::BIG},{78,3,figure,color,(int)ObjectId::BIG} };//free is needed
		break;
	default:
		break;
	}

}

Point** SpaceShip::getShipMat() {
	return shipMat;
}


void SpaceShip::move(Board* board) {

	switch (type)
	{
	case ShipSize::SMALL:
		checkSmallCollision(board);
		if (!isShipBlock) {
			moveShip(board,ObjectId::SMALL);
		}
		break;
	case ShipSize::BIG:
		checkBigCollision(board);
		if (!isShipBlock) {
			moveShip(board,ObjectId::BIG);
		}
		break;
	default:
		break;
	}
}

void  SpaceShip::initDraw() const {
	switch (type)
	{
	case ShipSize::SMALL:
		for (int i = 0; i < horizontalSize; i++) {
			shipMat[i]->draw();
		}
		break;
	case ShipSize::BIG:
		for (int i = 0; i < verticalSize; i++) {
			for (int j = 0; j < horizontalSize; j++) {
				shipMat[i][j].draw();
			}
		}
		break;
	default:
		break;
	}
}

void SpaceShip::moveShip(Board* board,ObjectId type) {


	for (int i = 0; i < verticalSize; i++)
	{
		for (int j = 0; j < horizontalSize; j++) {
			shipMat[i][j].draw((char)BoardFigure::EMPTY);
			board->getMat()[shipMat[i][j].getX()][shipMat[i][j].getY()].setFigure((char)BoardFigure::EMPTY);
			board->getMat()[shipMat[i][j].getX()][shipMat[i][j].getY()].setObjecId((char)ObjectId::EMPTY);
		}
	}


	for (int i = 0; i < verticalSize; i++)
	{
		for (int j = 0; j < horizontalSize; j++) {
			shipMat[i][j].move(direction);
			shipMat[i][j].draw();
			board->getMat()[shipMat[i][j].getX()][shipMat[i][j].getY()].setFigure(figure);
			board->getMat()[shipMat[i][j].getX()][shipMat[i][j].getY()].setObjecId((int)type);

		}
	}

}

void SpaceShip::checkBigCollision(Board* board) {
	vector<Block*> blocksInvolve;
	switch (direction) {
	case 0: // UP
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX(), shipMat[0][0].getY() - 1, direction, blocksInvolve, maxCarringBlockSize)) || (board->isNotEmptyPoint(shipMat[0][1].getX(), shipMat[0][1].getY() - 1, direction, blocksInvolve, maxCarringBlockSize));
		break;
	case 1: // DOWN
		isShipBlock = (board->isNotEmptyPoint(shipMat[1][0].getX(), shipMat[1][0].getY() + 1, direction, blocksInvolve, maxCarringBlockSize)) || (board->isNotEmptyPoint(shipMat[1][1].getX(), shipMat[1][1].getY() + 1, direction, blocksInvolve, maxCarringBlockSize));
		break;
	case 2: // LEFT
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX() - 1, shipMat[0][0].getY(), direction, blocksInvolve, maxCarringBlockSize)) || (board->isNotEmptyPoint(shipMat[1][0].getX() - 1, shipMat[1][0].getY(), direction, blocksInvolve, maxCarringBlockSize));
		if (!isShipBlock)
			shipCanPushMultipleBlocks(board, blocksInvolve);
		break;
	case 3: // RIGHT
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][1].getX() + 1, shipMat[0][1].getY(), direction, blocksInvolve, maxCarringBlockSize)) || (board->isNotEmptyPoint(shipMat[1][1].getX() + 1, shipMat[1][1].getY(), direction, blocksInvolve, maxCarringBlockSize));
		if (!isShipBlock) {
			shipCanPushMultipleBlocks(board, blocksInvolve);
		}
		break;
	default:
		isShipBlock = false;
		break;
	}
}



void SpaceShip::checkSmallCollision(Board* board) {
	vector<Block*> blocksInvolve;
	switch (direction) {
	case 0: // UP
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX(), shipMat[0][0].getY() - 1, direction, blocksInvolve, maxCarringBlockSize)) ||
			(board->isNotEmptyPoint(shipMat[0][1].getX(), shipMat[0][1].getY() - 1, direction, blocksInvolve, maxCarringBlockSize));
		break;
	case 1: // DOWN
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX(), shipMat[0][0].getY() + 1, direction, blocksInvolve, maxCarringBlockSize)) ||
			(board->isNotEmptyPoint(shipMat[0][1].getX(), shipMat[0][1].getY() + 1, direction, blocksInvolve, maxCarringBlockSize));
		break;
	case 2: // LEFT
		isShipBlock = board->isNotEmptyPoint(shipMat[0][0].getX() - 1, shipMat[0][0].getY(), direction, blocksInvolve, maxCarringBlockSize);
		if (!isShipBlock)
			shipCanPushMultipleBlocks(board, blocksInvolve);
		break;
	case 3: // RIGHT
		isShipBlock = board->isNotEmptyPoint(shipMat[0][1].getX() + 1, shipMat[0][1].getY(), direction, blocksInvolve, maxCarringBlockSize);
		if (!isShipBlock)
			shipCanPushMultipleBlocks(board, blocksInvolve);
		break;
	default:
		isShipBlock = false;
		break;
	}
}

void SpaceShip::shipCanPushMultipleBlocks(Board* board, vector<Block*>& blocksInvolve) {
	int sumSizeBlocks = 0;
	for (size_t i = 0; i < blocksInvolve.size(); i++) {
		sumSizeBlocks += blocksInvolve[i]->getSize();
	}
	if (sumSizeBlocks <= board->getBigShip()->getMaxCarringBlockSize()) {
		for (size_t i = 0; i < blocksInvolve.size(); i++) {
			blocksInvolve[i]->move(direction, board);
		}
	}
	else {
		isShipBlock = true;
	}
}




