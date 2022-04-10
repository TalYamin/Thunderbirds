#include "Ghost.h"

int Ghost::idGenerator = 1000;

Ghost::Ghost(Point** _list_points, int _size)
{
	list_points = new Point* ();
	for (int i = 0; i < _size; i++)
	{
		list_points[i] = _list_points[i];
	}
	size = _size;
	for (int i = 0; i < size; i++){
		list_points[i]->setObjecId(idGenerator++);
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

void Ghost::Move(Board* board){

	checkGhostCollision(board);
	if (isGhostBlock){
		switchDirection();
	}
	MoveGhost(board);
}

int Ghost::getSize()
{
	return size;
}

void Ghost::MoveGhost(Board* board) {

	auto mat = board->getMat();
	for (int i = 0; i < size; i++)
	{
		list_points[i]->draw((char)BoardFigure::EMPTY);
		mat[list_points[i]->getX(), list_points[i]->getY()]->setFigure((char)BoardFigure::EMPTY);
		mat[list_points[i]->getX(), list_points[i]->getY()]->setObjecId((int)ObjectId::EMPTY);

		list_points[i]->move(direction);
		list_points[i]->draw();
		mat[list_points[i]->getX(), list_points[i]->getY()]->setFigure(figure);
		mat[list_points[i]->getX(), list_points[i]->getY()]->setObjecId(ghostId);
	}
	
}

void Ghost::checkGhostCollision(Board* board)
{
	vector<Block*> blocksInvolve;
	switch (direction)
	{
	case 2: //LEFT
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() - 1, list_points[0]->getY(), direction, blocksInvolve, 0);
		break;
	case 3: //RIGHT
		isGhostBlock = board->isNotEmptyPoint(list_points[0]->getX() + 1, list_points[0]->getY(), direction, blocksInvolve, 0);
		break;
	default:
		isGhostBlock = false;
		break;
	}


}

void Ghost::switchDirection(){

	direction = direction == (int)Direction::RIGHT ? (int)Direction::LEFT : (int)Direction::RIGHT;

}

