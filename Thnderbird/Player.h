#pragma once
#include "Board.h"

class Player
{
	int lives;
	Board board;
public:
	Player();
	Player(Board _board)
	{
		board = _board;
	};
	~Player();
	void setLives(int _lives) { lives = _lives; };
	int getLives() { return lives; };
private:

};

Player::Player()
{
}

Player::~Player()
{
}