#pragma once
#include <iostream>
#include <conio.h>
#include "Player.h"

class Game
{
	Player player;
	enum { NO_SELECTION = 0, START = 1, INFO = 8, EXIT = 9, PAUSE_EXIT = 57 ,ESC = 27 };
	int userSelection = NO_SELECTION;
public:
	Game() {};
	~Game() {};
	void start();

private:
	void printMenu();
	void makeSelection();
	void run();
	void showInfo();
	void init();
	void pause();
};
