#pragma once
#include <iostream>
#include <conio.h>
#include "Spaceship.h"
#include "io_utils.h"
#include "Board.h"
#include "ShipStatus.h"
#define GAME_SPEED 200
#define TIME_TO_PAUSE 500
#define NO_DIRECTION -1
#define BIG_SWITCH_KEY 'B'
#define SMALL_SWITCH_KEY 'S'
#define COLORFUL 1
#define BLACK_WHITE 2
#define TIME_LEN 5

extern bool isBlackAndWhite;

class Game
{
	//data members
	GameStatus gameStatus = GameStatus::NO_SELECTION;
	GameStatus userSelection = GameStatus::NO_SELECTION;
	SpaceShip bigShip; //for testing
	SpaceShip smallShip; //for testing
	Board playingBoard;
	bool isBigMove = true;
	bool isBigOnMoving = false;
	bool isSmallOnMoving = false;
	bool isBigStart = false;
	bool isSmallStart = false;
	int lives = 3;

public:
	//ctors + dtors
	Game() {};
	~Game() {};

	//public methods
	void selectColorMode();
	void start();
	void setLives(int _lives);
	int getLives();


private:

	//private methods
	void printColorMenu();
	void setColorMode();
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
	char moveShip(bool& isStart, bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove, char curShipswitchKey, char otherShipSwitchKey);
	void checkVictory(SpaceShip& ship);
	void switchShip(bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove);
};

