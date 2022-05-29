#include "WonderGhost.h"
#include <time.h>

WonderGhost::WonderGhost(char _figure, vector<Point*> _list_points, int _seed) :Ghost(_list_points)
{
	srand(time(NULL));
	figure = _figure;
}

WonderGhost::~WonderGhost()
{
}


char WonderGhost::getFigure()
{
	return figure;
}
int WonderGhost::getDirection()
{
	return direction;
}
void WonderGhost::switchDirection()
{

	direction = (rand() % 4);
}

void WonderGhost::checkGhostCollision(Board* board)
{
	bool isGhost;
	vector<Block*> blocksInvolve;
	switch (direction)
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
	case (int)Direction::LEFT:
		this->setIsGhostBlock(board->isNotEmptyPoint(this->getListPoints()[0]->getX() - 1, this->getListPoints()[0]->getY(), this->getDirection(), blocksInvolve, 0, &isGhost));
		if (this->getIsGhostBlock()) {
			this->setIsGhostHit(isGhostHitShip(board, this->getListPoints()[0]->getX() - 1, this->getListPoints()[0]->getY()));
		}
		break;
	case (int)Direction::RIGHT:
		this->setIsGhostBlock(board->isNotEmptyPoint(this->getListPoints()[0]->getX() + 1, this->getListPoints()[0]->getY(), this->getDirection(), blocksInvolve, 0, &isGhost));
		if (this->getIsGhostBlock()) {
			this->setIsGhostHit(isGhostHitShip(board, this->getListPoints()[0]->getX() + 1, this->getListPoints()[0]->getY()));
		}
		break;
	default:
		setIsGhostBlock(false);
		break;
	}

}

void WonderGhost::Move(Board* board)
{
	do {
		this->switchDirection();
		checkGhostCollision(board);
	} while (getIsGhostBlock());
	if (!this->getIsGhostHit()) {
		this->MoveGhost(board);
	}
}

void WonderGhost::setDirection(int _direction)
{
	direction = _direction;
}
