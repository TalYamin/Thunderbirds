#pragma once
#include <iostream>
#include <conio.h>
#include "Spaceship.h"
#include "io_utils.h"
#include "Board.h"
#include "ShipStatus.h"
#define GAME_SPEED 200
#define TIME_TO_PAUSE 500

class Game
{
	//data members
	GameStatus gameStatus = GameStatus::NO_SELECTION;
	GameStatus userSelection = GameStatus::NO_SELECTION;
	SpaceShip bigShip; //for testing
	SpaceShip smallShip; //for testing
	Board playingBoard;
	int lives = 3;

public:
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

