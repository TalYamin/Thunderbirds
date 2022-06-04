#include "HorizontalGhost.h"


HorizontalGhost::HorizontalGhost(char _figure, vector <Point*> _list_points, int _size) : LineGhost(_list_points, _size)
{
	figure = _figure;
}

HorizontalGhost::~HorizontalGhost()
{
}

char HorizontalGhost::getFigure()
{
	return figure;
}

int HorizontalGhost::getDirection()
{
	return direction;
}

//chage the direction of the ghost
void HorizontalGhost::switchDirection()
{

	direction = direction == (int)Direction::RIGHT ? (int)Direction::LEFT : (int)Direction::RIGHT;

}

//Checking for collision with objects
void HorizontalGhost::checkGhostCollision(Board* board)
{
	bool isGhost;
	vector<Block*> blocksInvolve;
	switch (this->getDirection())
	{
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
