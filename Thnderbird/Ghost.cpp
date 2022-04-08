#include "Ghost.h"

int Ghost::idGenerator = 1000;

Ghost::Ghost(Point* _point)
{

	point = _point;
	point->setFigure(figure);
	point->setColor(color);
	point->setObjecId(idGenerator++);

}

Ghost::Ghost(Point* _point, char _figure, Color _color, bool _isGhostBlock, int _ghostId)
{

	point = _point;
	figure = _figure;
	color = _color;
	isGhostBlock = _isGhostBlock;
	ghostId = _ghostId;
}

Ghost::~Ghost()
{
}

void Ghost::Move(Board* board){

	checkGhostCollision(board);
	if (isGhostBlock){
		switchDirection();
	}
	MoveGhost(board);
}

void Ghost::MoveGhost(Board* board) {

	auto mat = board->getMat();
	point->draw((char)BoardFigure::EMPTY);
	mat[point->getX(), point->getY()]->setFigure((char)BoardFigure::EMPTY);
	mat[point->getX(), point->getY()]->setObjecId((int)ObjectId::EMPTY);

	point->move(direction);
	point->draw();
	mat[point->getX(), point->getY()]->setFigure(figure);
	mat[point->getX(), point->getY()]->setObjecId(ghostId);
}

void Ghost::checkGhostCollision(Board* board)
{
	vector<Block*> blocksInvolve;
	switch (direction)
	{
	case 2: //LEFT
		isGhostBlock = board->isNotEmptyPoint(point->getX() - 1, point->getY(), direction, blocksInvolve, 0);
		break;
	case 3: //RIGHT
		isGhostBlock = board->isNotEmptyPoint(point->getX() + 1, point->getY(), direction, blocksInvolve, 0);
		break;
	default:
		isGhostBlock = false;
		break;
	}


}

void Ghost::switchDirection(){

	direction = direction == (int)Direction::RIGHT ? (int)Direction::LEFT : (int)Direction::RIGHT;

}

