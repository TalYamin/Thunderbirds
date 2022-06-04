#include "LineGhost.h"

LineGhost::LineGhost(vector<Point*> _list_points, int _size) : Ghost(_list_points)
{
}

LineGhost::~LineGhost()
{
}
//move a ghost by his direction.
void LineGhost::Move(Board* board)
{
	checkGhostCollision(board);
	if (this->getIsGhostBlock()) {
		this->switchDirection();
	}
	if (!this->getIsGhostHit()) {
		this->MoveGhost(board);
	}
}
