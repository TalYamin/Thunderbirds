#include "Board.h"
#define FIGURE ' '


void Board::revertStartUpBoard()
{
}

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
			Point* point = new Point(x, y, boardData[i], Color::WHITE);
			setMatrixPoint(x, y, point);
			x++;
		}
	}
	initBlocks();
}

void Board::draw()
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


bool Board::isNotEmptyPoint(int x, int y) {

	if (x >= HORIZONTAL_SIZE || y >= VERTICAL_SIZE) {
		return false;
	}
	else if (this->getMat()[x][y].getFigure() == ' ') {
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

	Point* block1Point1 = new Point(5, 2, (char)BoardFigure::BLOCK, Color::RED);

	Point* blockList1[] = { block1Point1 };
	Block* block1 = new Block(blockList1, firstBlockSize);

	insertNewBlock(block1);

	Point* block2Point1 = new Point(35, 9, (char)BoardFigure::BLOCK, Color::RED);
	Point* block2Point2 = new Point(36, 9, (char)BoardFigure::BLOCK, Color::RED);
	Point* block2Point3 = new Point(35, 10, (char)BoardFigure::BLOCK, Color::RED);
	Point* block2Point4 = new Point(36, 10, (char)BoardFigure::BLOCK, Color::RED);

	Point* blockList2[] = { block2Point1,block2Point2,block2Point3,block2Point4 };
	Block* block2 = new Block(blockList2, secondBlockSize);
	insertNewBlock(block2);

	Point* block3Point1 = new Point(55, 18, (char)BoardFigure::BLOCK, Color::RED);
	Point* block3Point2 = new Point(56, 18, (char)BoardFigure::BLOCK, Color::RED);
	Point* block3Point3 = new Point(57, 18, (char)BoardFigure::BLOCK, Color::RED);

	Point* blockList3[] = { block3Point1,block3Point2,block3Point3 };
	Block* block3 = new Block(blockList3, thiredBlockSize);
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