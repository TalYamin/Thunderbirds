#include "Ghost.h"

int Ghost::idGenerator = 1000;

Ghost::Ghost(Point** _list_points, int _size)
{
	list_points = new Point * ();
	for (int i = 0; i < _size; i++)
	{
		list_points[i] = _list_points[i];
	}
	size = _size;
	ghostId = idGenerator++;
	for (int i = 0; i < _size; i++) {
		list_points[i]->setObjecId(ghostId);
	}
}

Ghost::Ghost(Point** _list_points, char _figure, Color _color, bool _isGhostBlock, int _ghostId)
{

	list_points = _list_points;
	figure = _figure;
	color = _color;
	isGhostBlock = _isGhostBlock;
	ghostId = _ghostId;
}

Ghost::~Ghost()
{
}

void Ghost::Move(Board* board) {

	checkGhostCollision(board);
	if (isGhostBlock) {
		switchDirection();
	}
	if (!isGhostHit){
		MoveGhost(board);
	}
}

int Ghost::getSize()
{
	return size;
}

void Ghost::MoveGhost(Board* board) {

	for (int i = 0; i < size; i++)
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
	bool isShipHit;
	switch (direction)
	{
	case 2: //LEFT
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() - 1, list_points[0]->getY(), direction, blocksInvolve, 0);
		if (isGhostBlock){
			isGhostHit = isGhostHitShip(board, list_points[0]->getX() - 1, list_points[0]->getY());
		}
		break;
	case 3: //RIGHT
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() + 1, list_points[0]->getY(), direction, blocksInvolve, 0);
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