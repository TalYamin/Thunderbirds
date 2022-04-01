#include "Board.h"
#define FIGURE ' '



void Board::initBoard()
{
	timeRemains = MAX_TIME;
	size_t boardLen;
	int y = 0;
	int x = 0;
	const char* boardData = R""""(++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++                          +                       +                     +
+                                +                       +                     +
+++++++                          +                       +                     +
+                                +                       +                     +
+       +                        +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                                        +                     +
+                                                        +                     +
+                                +++++++++               +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +           +++++++++++++                     +
+                                +                                             +
+                                +                                             +
+                                +    ++++++++++++++++++++                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
++++++++++++++++++++++++++++++++++++++++++    ++++++++++++++++++++++++++++++++++)"""";
	boardLen = strlen(boardData);
	for (int i = 0; i < boardLen; i++)
	{
		if (boardData[i] == '\n') {
			y++;
			x = 0;
		}
		else
		{
			int objectId = CheckObjectId(boardData[i]);
			Point* point = new Point(x, y, boardData[i], Color::WHITE, objectId);
			setMatrixPoint(x, y, point);
			x++;
		}
	}
	initBlocks();
}

int Board::CheckObjectId(char ch) const {
	return ch == (char)BoardFigure::EMPTY ? (int)ObjectId::EMPTY : (int)ObjectId::WALL;

}

void Board::draw() const
{
	for (int i = 0; i < maxVerticalSize; i++)
	{
		for (int j = 0; j < maxHorizontalSize; j++)
		{
			mat[j][i].draw();
		}
		cout << endl;
	}
	cout << endl;
}

void Board::setMatrixPoint(int _x, int _y, Point* _p)
{
	mat[_x][_y] = *_p;
}


bool Board::isNotEmptyPoint(int x, int y) const {

	if (x >= HORIZONTAL_SIZE || y >= VERTICAL_SIZE) {
		return false;
	}
	else if (mat[x][y].getFigure() == ' ') {
		return false;
	}
	else {
		return true;
	}
}

void Board::initBlocks()
{
	blocksAmount = 0;
	int firstBlockSize = 1;
	int secondBlockSize = 4;
	int thiredBlockSize = 3;

	Point* block1Point1 = new Point(5, 2, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);

	Point* blockList1[] = { block1Point1 };
	Block* block1 = new Block(blockList1, firstBlockSize, blocksAmount);

	insertNewBlock(block1);

	Point* block2Point1 = new Point(35, 9, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block2Point2 = new Point(36, 9, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block2Point3 = new Point(35, 10, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block2Point4 = new Point(36, 10, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);

	Point* blockList2[] = { block2Point1,block2Point2,block2Point3,block2Point4 };
	Block* block2 = new Block(blockList2, secondBlockSize, blocksAmount);
	insertNewBlock(block2);

	Point* block3Point1 = new Point(55, 18, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block3Point2 = new Point(56, 18, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block3Point3 = new Point(57, 18, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);

	Point* blockList3[] = { block3Point1,block3Point2,block3Point3 };
	Block* block3 = new Block(blockList3, thiredBlockSize, blocksAmount);
	insertNewBlock(block3);

	placeBlocksOnBoard();

}

void Board::placeBlocksOnBoard()
{
	int blockSize;
	Block* block;
	for (int i = 0; i < blocksAmount; i++)
	{
		block = allBlocks[i];
		blockSize = block->getSize();
		for (int j = 0; j < blockSize; j++)
		{
			Point* blockPoint = block->getListPoints()[j];
			setMatrixPoint(blockPoint->getX(), blockPoint->getY(), blockPoint);
		}
	}
}

void Board::insertNewBlock(Block* block)
{
	blocksAmount++;
	//TODO: Memory check allocation
	allBlocks[blocksAmount - 1] = block;
}

Board::Board(int _maxHorizontalSize, int _maxVerticalSize, long _timeRemains) {
	maxHorizontalSize = _maxHorizontalSize;
	maxVerticalSize = _maxVerticalSize;
	timeRemains = _timeRemains;
}

Board::Board()
{

}


bool Board::checkExit(SpaceShip ship) {

	switch (ship.getType())
	{
	case ShipSize::BIG:

		if ((ship.getShipMat()[0][0].getX() == EXIT_X1 && ship.getShipMat()[0][0].getY() == EXIT_Y) || (ship.getShipMat()[0][0].getX() == EXIT_X2 && ship.getShipMat()[0][0].getY() == EXIT_Y) || (ship.getShipMat()[0][0].getX() == EXIT_X3 && ship.getShipMat()[0][0].getY() == EXIT_Y)) {
			removeShipFromBoard(ship);
			return true;
		}
		else {
			return false;
		}

		break;
	case ShipSize::SMALL:
		if ((ship.getShipMat()[0]->getX() == EXIT_X1 && ship.getShipMat()[0]->getY() == EXIT_Y) || (ship.getShipMat()[0]->getX() == EXIT_X2 && ship.getShipMat()[0]->getY() == EXIT_Y) || (ship.getShipMat()[0]->getX() == EXIT_X3 && ship.getShipMat()[0]->getY() == EXIT_Y)) {
			removeShipFromBoard(ship);
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		break;
	}
}

void Board::removeShipFromBoard(SpaceShip ship) {

	switch (ship.getType())
	{
	case ShipSize::BIG:
		for (int i = 0; i < ship.getVerticalSize(); i++)
		{
			for (int j = 0; j < ship.getHorizontalSize(); j++) {
				ship.getShipMat()[i][j].draw((char)BoardFigure::EMPTY);
				mat[ship.getShipMat()[i][j].getX()][ship.getShipMat()[i][j].getY()].setFigure((char)BoardFigure::EMPTY);
			}
		}
		break;
	case ShipSize::SMALL:
		for (int i = 0; i < ship.getHorizontalSize(); i++) {
			ship.getShipMat()[i]->draw((char)BoardFigure::EMPTY);
			mat[ship.getShipMat()[i]->getX()][ship.getShipMat()[i]->getY()].setFigure((char)BoardFigure::EMPTY);
		}
		break;
	default:
		break;
	}

}

Block* Board::getBlockById(int objectId) const {
	for (int i = 0; i < blocksAmount; i++) {
		if (allBlocks[i]->getblockId() == objectId) {
			return allBlocks[i];
		}
	}
}

void Board::setTimeRemains(long timeToSet) {
	timeRemains = timeToSet;
}

long Board::getTimeRemains() const{
	return timeRemains;
}

void Board::timeDown() {
	timeRemains--;
}

void Board::setMaxHorizontalSize(int _horizontal) {
	maxHorizontalSize = _horizontal;
};

int Board::getMaxHorizontalSize() const{ 
	return maxHorizontalSize; 
}

void Board::setGetMaxVerticalSize(int _vertical) {
	maxVerticalSize = _vertical; 
}

int Board::getMaxVerticalSize() const {
	return maxVerticalSize;
}

Point (*Board::getMat())[25]{
	return mat; 
};


Board::~Board() {

}


