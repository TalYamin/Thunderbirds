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
+      +                         +                       +                     +
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

int Board::CheckObjectId(char ch) {
	return ch == (char)BoardFigure::EMPTY ? (int)ObjectId::EMPTY : (int)ObjectId::WALL;

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

void Board::fallBlocksIfNoFloor()
{
	bool needToFall;
	for (int i = 0;i < blocksAmount;i++)
	{
		Block* block = allBlocks[i];
		needToFall = true;
		for (int j = 0;j < block->getSize();j++) {

			if (!isPointNoFloor(block->getListPoints()[j]->getX(), block->getListPoints()[j]->getY() + 1, block->getblockId()))
			{
				needToFall = false;
				break;
			}
		}
		if (needToFall == true)
		{
			block->fall(this);
		}
		needToFall = true;
	}
}

bool Board::isPointNoFloor(int x, int y, int blockId) {
	Point point = mat[x][y];
	if (point.getObjecId() == (int)ObjectId::EMPTY || point.getObjecId() == blockId)
		return true;
	return false;
}


bool Board::isNotEmptyPoint(int x, int y, int direction, vector<Block*>& blocksInvolve) {

	if (x >= HORIZONTAL_SIZE || y >= VERTICAL_SIZE) {
		return false;
	}
	else if (mat[x][y].getFigure() == (char)BoardFigure::EMPTY) {
		return false;
	}
	else if (mat[x][y].getFigure() == (char)BoardFigure::BLOCK)
	{
		int BlockId = mat[x][y].getObjecId();
		Block* block = getBlockById(BlockId);

		if ((direction == 2 || direction == 3) && isBlockCanMove(block, direction))
		{
			int BlockId = mat[x][y].getObjecId();
			Block* block = getBlockById(BlockId);
			if (find(blocksInvolve.begin(), blocksInvolve.end(), block) == blocksInvolve.end())
				blocksInvolve.push_back(block);
			return false;
		}
	}
	return true;

}

bool Board::isBlockCanMove(Block* block, int direction)
{
	int blockSize = block->getSize();
	if (direction == 2)//LEFT
	{
		for (int i = 0;i < block->getSize();i++)
		{
			Point* point = block->getListPoints()[i];
			if (isValidPlace(point->getX() - 1, point->getY(), block))
				return false;
		}
	}
	else if (direction == 3)//RIGHT
	{
			for (int i = 0;i < block->getSize();i++)
			{
				Point* point = block->getListPoints()[i];
				if (isValidPlace(point->getX() + 1, point->getY(), block))
					return false;
			}
	}
	return true;
}

bool Board::isValidPlace(int x, int y, Block* block)
{
	return  (mat[x][y].getObjecId() != (int)ObjectId::EMPTY && mat[x][y].getObjecId() != block->getblockId());
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

Block* Board::getBlockById(int objectId) {
	for (int i = 0; i < blocksAmount; i++) {
		if (allBlocks[i]->getblockId() == objectId) {
			return allBlocks[i];
		}
	}
}