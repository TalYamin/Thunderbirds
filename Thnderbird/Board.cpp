#include "Board.h"
#define FIGURE ' '


void Board::revertStartUpBoard()
{
}

void Board::initBoard()
{
	timeRemains = 10000;
	size_t boardLen;
	int row = 0;
	int col = 0;
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
			row++;
			col = 0;
		}
		else
		{
			Point* point = new Point(col, row, boardData[i]);
			setMatrixPoint(col, row, point);
			col++;
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