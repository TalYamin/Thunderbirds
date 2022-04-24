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

Ghost::Ghost(vector <Point*> _list_points, char _figure, Color _color, bool _isGhostBlock, int _ghostId)
{

	list_points = _list_points;
	figure = _figure;
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
Move and check collision of the ghost.
*/
void Ghost::Move(Board* board) {

	checkGhostCollision(board);
	if (isGhostBlock) {
		switchDirection();
	}
	if (!isGhostHit) {
		MoveGhost(board);
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

/*
Responible for the ghost movement animation.
*/
void Ghost::MoveGhost(Board* board) {

	for (int i = 0; i < list_points.size(); i++)
	{
		list_points[i]->draw((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure((char)BoardFigure::EMPTY);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setObjecId((int)ObjectId::EMPTY);

		list_points[i]->move(direction);
		list_points[i]->draw();
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setFigure(figure);
		board->getMat()[list_points[i]->getX()][list_points[i]->getY()].setObjecId(ghostId);
	}

}

void Ghost::checkGhostCollision(Board* board)
{
	vector<Block*> blocksInvolve;
	bool isWallInvolved = false;
	switch (direction)
	{
	case (int)Direction::LEFT:
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() - 1, list_points[0]->getY(), direction, blocksInvolve, 0, nullptr, &isWallInvolved);
		if (isGhostBlock) {
			isGhostHit = isGhostHitShip(board, list_points[0]->getX() - 1, list_points[0]->getY());
		}
		break;
	case (int)Direction::RIGHT:
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() + 1, list_points[0]->getY(), direction, blocksInvolve, 0, nullptr, &isWallInvolved);
		if (isGhostBlock) {
			isGhostHit = isGhostHitShip(board, list_points[0]->getX() + 1, list_points[0]->getY());
		}
		break;
	default:
		isGhostBlock = false;
		break;
	}


}

void Ghost::switchDirection() {

	direction = direction == (int)Direction::RIGHT ? (int)Direction::LEFT : (int)Direction::RIGHT;

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