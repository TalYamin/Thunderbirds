#pragma once
#include "Player.h"
#define NO_SELECTION 0
#define START 1
#define INFO 8
#define EXIT 9

class Game
{
	Player player;
	enum { ESC = 27 };
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
};
