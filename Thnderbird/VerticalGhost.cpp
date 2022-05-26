#include "VerticalGhost.h"

VerticalGhost::VerticalGhost(char _figure, vector<Point*> _list_points, int _size) : LineGhost(_list_points, _size)
{
    figure = _figure;
}

VerticalGhost::~VerticalGhost()
{
}

char VerticalGhost::getFigure()
{
    return figure;
}

int VerticalGhost::getDirection()
{
    return direction;
}

void VerticalGhost::switchDirection()
{
    direction = direction == (int)Direction::UP ? (int)Direction::DOWN : (int)Direction::UP;

}

void VerticalGhost::checkGhostCollision(Board* board){

	bool isGhost;
	vector<Block*> blocksInvolve;
	switch (this->getDirection())
	{
	case (int)Direction::UP:
		this->setIsGhostBlock(board->isNotEmptyPoint(this->getListPoints()[0]->getX(), this->getListPoints()[0]->getY() - 1, this->getDirection(), blocksInvolve, 0, &isGhost));
		if (this->getIsGhostBlock()) {
			this->setIsGhostHit(isGhostHitShip(board, this->getListPoints()[0]->getX(), this->getListPoints()[0]->getY() - 1));
		}
		break;
	case (int)Direction::DOWN:
		this->setIsGhostBlock(board->isNotEmptyPoint(this->getListPoints()[0]->getX(), this->getListPoints()[0]->getY() + 1, this->getDirection(), blocksInvolve, 0, &isGhost));
		if (this->getIsGhostBlock()) {
			this->setIsGhostHit(isGhostHitShip(board, this->getListPoints()[0]->getX(), this->getListPoints()[0]->getY() + 1));
		}
		break;
	default:
		setIsGhostBlock(false);
		break;
	}

}
