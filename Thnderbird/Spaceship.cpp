#include "Spaceship.h"


/*
Constructor of SpaceShip.
*/
SpaceShip::SpaceShip(int _verticalSize, int _horizontalSize, char _figure, Color _color, int _maxCarringBlockSize, ShipSize _type) {

	verticalSize = _verticalSize;
	horizontalSize = _horizontalSize;
	figure = _figure;
	color = _color;
	maxCarringBlockSize = _maxCarringBlockSize;
	type = _type;
}


/*
This is setter function for type data member.
*/
void SpaceShip::setType(int typeNum) {
	type = static_cast<ShipSize>(typeNum);
}

/*
This is getter function for type data member.
*/
ShipSize SpaceShip::getType() const {
	return type;
}

/*
This is setter function for vertical size data member.
*/
void SpaceShip::setVerticalSize(int _verticalSize) {
	verticalSize = _verticalSize;
}

/*
This is getter function for vertical size data member.
*/
int SpaceShip::getVerticalSize() const {
	return verticalSize;
}

/*
This is setter function for horizontal size data member.
*/
void SpaceShip::setHorizontalSize(int _horizontalSize) {
	horizontalSize = _horizontalSize;
}

/*
This is getter function for horizontal size data member.
*/
int SpaceShip::getHorizontalSize() const {
	return horizontalSize;
}

/*
This is setter function for direction data member.
*/
void SpaceShip::setDirection(int _direction) {
	direction = _direction;
}

/*
This is getter function for direction data member.
*/
int SpaceShip::getDirection(char key) const {
	for (int i = 0; i < NUM_ARROW_KEYS; i++)
	{
		if (key == tolower(arrowKeys[i]) || key == toupper(arrowKeys[i]))
			return i;
	}
	return NO_DIRECTION;
}

/*
This is setter function for figure data member.
*/
void SpaceShip::setFigure(const char c) {
	figure = c;
}
/*
This is getter function for figure data member.
*/
char SpaceShip::getFigure() const {
	return figure;
}

/*
This is setter function for arrow keys data member.
*/
void SpaceShip::setArrowKeys(const char* keys) { // "wzad"
	for (int i = 0; i < NUM_ARROW_KEYS; i++)
	{
		arrowKeys[i] = keys[i];
	}
};

/*
This is setter function for color data member.
*/
void SpaceShip::setColor(Color _color) {
	color = _color;
}

/*
This is getter function for color data member.
*/
Color SpaceShip::getColor() const {
	return color;
}

/*
This is setter function for is ship block data member.
*/
void SpaceShip::setIsShipBlock() {
	isShipBlock == true ? isShipBlock = false : isShipBlock = true;
};

/*
This is getter function for is ship block data member.
*/
bool SpaceShip::getIsShipBlock() const {
	return isShipBlock;
}

/*
This is getter function for carring block size data member.
*/
int SpaceShip::getMaxCarringBlockSize()
{
	return maxCarringBlockSize;
}


/*
This is setter function for carring block size data member.
*/
void SpaceShip::setMaxCarringBlockSize(int _maxCarringBlockSize)
{
	maxCarringBlockSize = _maxCarringBlockSize;
}

/*
This is setter function of is exit data member.
*/
void SpaceShip::setIsExit(bool _isExit) {
	isExit = _isExit;
};

/*
This is getter function of is exit data member.
*/
bool SpaceShip::getIsExit() const {
	return isExit;
}

/*
This is setter function of is die data member.
*/
void SpaceShip::setIsDie(bool _isDie) {
	isDie = _isDie;
};

/*
This is getter function of is die data member.
*/
bool SpaceShip::getIsDie() const {
	return isDie;
}

/*
This function is used set ship points matrix.
*/
void SpaceShip::setupShipMat(int x, int y) {

	switch (type)
	{
	case ShipSize::SMALL:
		shipMat[0] = new Point[2]{ {x,y,figure,color,(int)ObjectId::SMALL},{x + 1,y,figure,color,(int)ObjectId::SMALL} };
		break;
	case ShipSize::BIG:
		shipMat[0] = new Point[2]{ {x,y,figure,color,(int)ObjectId::BIG},{x + 1,y,figure,color,(int)ObjectId::BIG} };
		shipMat[1] = new Point[2]{ {x,y + 1,figure,color,(int)ObjectId::BIG},{x + 1,y + 1,figure,color,(int)ObjectId::BIG} };
		break;
	default:
		break;
	}

}

/*
This function is used get ship matrix.
*/
Point** SpaceShip::getShipMat() {
	return shipMat;
}

/*
This function is used to move ship.
Accoridng to ship type, there is function which check collision.
In case there is no collision, calls to moveShip function.
*/
void SpaceShip::move(Board* board) {

	switch (type)
	{
	case ShipSize::SMALL:
		checkSmallCollision(board);
		if (!isShipBlock) {
			moveShip(board, ObjectId::SMALL);
		}
		break;
	case ShipSize::BIG:
		checkBigCollision(board);
		if (!isShipBlock) {
			moveShip(board, ObjectId::BIG);
		}
		break;
	default:
		break;
	}
}

/*
This function is used to draw ships.
*/
void  SpaceShip::initDraw() const {

	for (int i = 0; i < verticalSize; i++) {
		for (int j = 0; j < horizontalSize; j++) {
			shipMat[i][j].draw();
		}
	}
}

/*
This function is used to move ship.
First, function clean the previous location of ship. Remove figures from board and update
board matrix. Then, function draws ship figure on board in new location and update board matrix.
*/
void SpaceShip::moveShip(Board* board, ObjectId type) {


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

/*
This function is used to check big ship collision, according to indexes of point that ship is
going to move to and according to direction. Collision check is done by using isNotEmptyPoint()
function. In case of left and right, if there is no block - checking if shipCanPushMultipleBlocks().
*/
void SpaceShip::checkBigCollision(Board* board) {
	vector<Block*> blocksInvolve;
	bool isGhost = false;
	switch (direction) {
	case (int)Direction::UP:
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX(), shipMat[0][0].getY() - 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost)) || (board->isNotEmptyPoint(shipMat[0][1].getX(), shipMat[0][1].getY() - 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost));
		break;
	case (int)Direction::DOWN:
		isShipBlock = (board->isNotEmptyPoint(shipMat[1][0].getX(), shipMat[1][0].getY() + 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost)) || (board->isNotEmptyPoint(shipMat[1][1].getX(), shipMat[1][1].getY() + 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost));
		break;
	case (int)Direction::LEFT:
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX() - 1, shipMat[0][0].getY(), direction, blocksInvolve, maxCarringBlockSize, &isGhost)) || (board->isNotEmptyPoint(shipMat[1][0].getX() - 1, shipMat[1][0].getY(), direction, blocksInvolve, maxCarringBlockSize, &isGhost));
		if (!isShipBlock)
			shipCanPushMultipleBlocks(board, blocksInvolve);
		break;
	case (int)Direction::RIGHT:
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][1].getX() + 1, shipMat[0][1].getY(), direction, blocksInvolve, maxCarringBlockSize, &isGhost)) || (board->isNotEmptyPoint(shipMat[1][1].getX() + 1, shipMat[1][1].getY(), direction, blocksInvolve, maxCarringBlockSize, &isGhost));
		if (!isShipBlock) {
			shipCanPushMultipleBlocks(board, blocksInvolve);
		}
		break;
	default:
		isShipBlock = false;
		break;
	}
	if (isGhost) {
		isDie = true;
	}
}


/*
This function is used to check small ship collision, according to indexes of point that ship is
going to move to and according to direction. Collision check is done by using isNotEmptyPoint()
function. In case of left and right, if there is no block - checking if shipCanPushMultipleBlocks().
*/
void SpaceShip::checkSmallCollision(Board* board) {
	vector<Block*> blocksInvolve;
	bool isGhost = false;
	switch (direction) {
	case (int)Direction::UP:
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX(), shipMat[0][0].getY() - 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost)) ||
			(board->isNotEmptyPoint(shipMat[0][1].getX(), shipMat[0][1].getY() - 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost));
		break;
	case (int)Direction::DOWN:
		isShipBlock = (board->isNotEmptyPoint(shipMat[0][0].getX(), shipMat[0][0].getY() + 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost)) ||
			(board->isNotEmptyPoint(shipMat[0][1].getX(), shipMat[0][1].getY() + 1, direction, blocksInvolve, maxCarringBlockSize, &isGhost));
		break;
	case (int)Direction::LEFT:
		isShipBlock = board->isNotEmptyPoint(shipMat[0][0].getX() - 1, shipMat[0][0].getY(), direction, blocksInvolve, maxCarringBlockSize, &isGhost);
		if (!isShipBlock)
			shipCanPushMultipleBlocks(board, blocksInvolve);
		break;
	case (int)Direction::RIGHT:
		isShipBlock = board->isNotEmptyPoint(shipMat[0][1].getX() + 1, shipMat[0][1].getY(), direction, blocksInvolve, maxCarringBlockSize, &isGhost);
		if (!isShipBlock)
			shipCanPushMultipleBlocks(board, blocksInvolve);
		break;
	default:
		isShipBlock = false;
		break;
	}
	if (isGhost) {
		isDie = true;
	}
}

/*
This function is used check if ship can move multiple blocks.
Function sum the size of blocks which involved and in case it is less than max carring
so moving blocks. In other case, update isShipBlock to false.
*/
void SpaceShip::shipCanPushMultipleBlocks(Board* board, vector<Block*>& blocksInvolve) {
	int sumSizeBlocks = 0;
	for (size_t i = 0; i < blocksInvolve.size(); i++) {
		sumSizeBlocks += (int)blocksInvolve[i]->getListPoints().size();
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


/*
Distructor of SpaceShip.
*/
SpaceShip::~SpaceShip() {
	switch (type)
	{
	case ShipSize::SMALL:
		delete[] shipMat[0];
		break;
	case ShipSize::BIG:
		delete[] shipMat[0];
		delete[] shipMat[1];
		break;
	default:
		break;
	}
}

