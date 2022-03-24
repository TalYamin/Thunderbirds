#pragma once
#include <iostream>
#include <conio.h>
#include "Player.h"
#include "Spaceship.h"
#include "io_utils.h"

class Game
{
	//data members
	Player player;
	enum { NO_SELECTION = 0, START = 1, INFO = 8, EXIT = 9, PAUSE_EXIT = 57 , ESC = 27 };
	int userSelection = NO_SELECTION;
	SpaceShip bigShip; //for testing
	SpaceShip smallShip; //for testing
public:

	//ctors + dtors
	Game() {};
	~Game() {};
	
	//public methods
	void start();

private:

	//private methods
	void printMenu();
	void makeSelection();
	void run();
	void showInfo();
	void init();
	void pause();
};
