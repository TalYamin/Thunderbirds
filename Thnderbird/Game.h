#pragma once
#include <iostream>
#include <conio.h>
#include "Spaceship.h"
#include "io_utils.h"
#include "Board.h"
#include "ShipStatus.h"

class Game
{
	//data members
	enum { NO_SELECTION = 0, START = 1, INFO = 8, EXIT = 9, PAUSE_EXIT = 57, ESC = 27 };
	int userSelection = NO_SELECTION;
	SpaceShip bigShip; //for testing
	SpaceShip smallShip; //for testing
	Board playingBoard;
	int lives = 3;

public:
	static GameStatus gameStatus;
	//ctors + dtors
	Game() {};
	~Game() {};

	//public methods
	void start();
	void setLives(int _lives);
	int getLives();


private:

	//private methods
	void printMenu();
	void makeSelection();
	void run();
	void showInfo();
	void init();
	void pause();
	void pauseCheck(int logY);
	void printTime(int x, int y);
	void printTextDescription(int x, int y, const char* text);
	void printLives(int x, int y);
	void gameMetadata(SpaceShip ship);
	void deadHeartHandler();
	bool isDie();
	bool timeoutHandler();
	void drawIcon(SpaceShip ship);
	void deleteIcon(SpaceShip ship);
	bool bulkSmash();
};
