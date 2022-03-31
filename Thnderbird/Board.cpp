#include "Board.h"

#define FIGURE ' '


void Board::revertStartUpBoard()
{
}

void Board::initBoard()
{
	timeRemains = 10000;
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
	for (int i = 0;i < boardLen;i++)
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
}

void Board::draw()
{
	for (int i = 0;i < maxVerticalSize;i++)
	{
		for (int j = 0;j < maxHorizontalSize;j++)
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

	if (this->getMat()[x][y].getFigure() == ' ')
		return false;
	else
		return true;
}

void Board::initBlocks()
{
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
	for (int i = 0;i < blocksAmount;i++)
	{
		block = allBlocks[i];
		blockSize = block->getSize();
		for (int j = 0;j < blockSize;j++)
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
	initBoard();
	initBlocks();
}