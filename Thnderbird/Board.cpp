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
			Point* point = new Point(x, y, boardData[i]);
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

bool Board::checkExit(SpaceShip ship) {

	switch (ship.getType())
	{
	case ShipSize::BIG:

			if ((ship.getShipMat()[0][0].getX() == EXIT_X1 && ship.getShipMat()[0][0].getY() == EXIT_Y) || (ship.getShipMat()[0][0].getX() == EXIT_X2 && ship.getShipMat()[0][0].getY() == EXIT_Y) || (ship.getShipMat()[0][0].getX() == EXIT_X3 && ship.getShipMat()[0][0].getY() == EXIT_Y)) {
				return true;
			}
			else {
				return false;
			}
		
		break;
	case ShipSize::SMALL:
			if ((ship.getShipMat()[0]->getX() == EXIT_X1 && ship.getShipMat()[0]->getY() == EXIT_Y) || (ship.getShipMat()[0]->getX() == EXIT_X2 && ship.getShipMat()[0]->getY() == EXIT_Y) || (ship.getShipMat()[0]->getX() == EXIT_X3 && ship.getShipMat()[0]->getY() == EXIT_Y)) {
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