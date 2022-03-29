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