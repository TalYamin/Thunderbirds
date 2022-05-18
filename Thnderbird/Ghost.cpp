#include "Ghost.h"

int Ghost::idGenerator = START_GHOST_ID;

Ghost::Ghost(vector <Point*> _list_points, int _size)
{
	list_points = _list_points;
	ghostId = idGenerator++;
	for (int i = 0; i < list_points.size(); i++) {
		list_points[i]->setObjecId(ghostId);
	}
}

Ghost::Ghost(vector <Point*> _list_points, Color _color, bool _isGhostBlock, int _ghostId)
{

	list_points = _list_points;
	color = _color;
	isGhostBlock = _isGhostBlock;
	ghostId = _ghostId;
}
/*
d'tor of ghost.
*/
Ghost::~Ghost()
{
	for (int i = 0;i < size;i++)
	{
		delete(list_points[i]);
	}
}



/*
Get the size of the ghost.
*/
int Ghost::getSize()
{
	return size;
}

/*
Get the Unique id of the ghost
*/
int Ghost::getId()
{
	return ghostId;
}

/*
Get all of the ghost points.
*/
vector<Point*> Ghost::getListPoints()
{
	return list_points;
}

bool Ghost::getIsGhostBlock()
{
	return isGhostBlock;
}

bool Ghost::getIsGhostHit()
{
	return isGhostHit;
}

/*
Responible for the ghost movement animation.
*/
void Ghost::MoveGhost(Board* board) {

	for (int i = 0; i < list_points.size(); i++)
	{
		list_points[i]->draw((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setObjecId((int)ObjectId::EMPTY);

		list_points[i]->move(this->getDirection());
		list_points[i]->draw();
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure(this->getFigure());
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setObjecId(ghostId);
	}

}

void Ghost::checkGhostCollision(Board* board)
{
	vector<Block*> blocksInvolve;
	switch (this->getDirection())
	{
	case (int)Direction::LEFT:
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() - 1, list_points[0]->getY(), this->getDirection(), blocksInvolve, 0, nullptr);
		if (isGhostBlock) {
			isGhostHit = isGhostHitShip(board, list_points[0]->getX() - 1, list_points[0]->getY());
		}
		break;
	case (int)Direction::RIGHT:
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() + 1, list_points[0]->getY(), this->getDirection(), blocksInvolve, 0, nullptr);
		if (isGhostBlock) {
			isGhostHit = isGhostHitShip(board, list_points[0]->getX() + 1, list_points[0]->getY());
		}
		break;
	default:
		isGhostBlock = false;
		break;
	}


}


bool Ghost::isGhostHitShip(Board* board, int x, int y) {

	int currObjectId = board->getMat()[x][y].getObjecId();
	if (currObjectId == (int)ObjectId::BIG) {
		board->getBigShip()->setIsDie(true);
		return true;
	}
	else if (currObjectId == (int)ObjectId::SMALL) {
		board->getSmallShip()->setIsDie(true);
		return true;
	}
	return false;

}