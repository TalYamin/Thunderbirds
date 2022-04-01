#pragma once
#include <iostream>
#include <conio.h>
#include "Spaceship.h"
#include "io_utils.h"
#include "Board.h"
#include "GameStatus.h"
#define GAME_SPEED 50
#define TIME_TO_PAUSE 500
#define NO_DIRECTION -1
#define BIG_SWITCH_KEY 'B'
#define SMALL_SWITCH_KEY 'S'
#define COLORFUL 1
#define BLACK_WHITE 2
#define TIME_LEN 5
#define BIG_SHIP_CARRING_SIZE 6
#define SMALL_SHIP_CARRING_SIZE 2

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
	Game() = default;
	Game(const Game& _game) = default;
	Game& operator=(const Game& _game) = default;
	~Game();

	//getters + setters
	void setLives(int _lives);
	int getLives() const;

	//public methods
	void selectColorMode() const;
	void start();


private:

	//private methods
	void printColorMenu() const;
	void setColorMode() const;
	void printMenu() const;
	void makeSelection();
	void run();
	void showInfo() const;
	void init();
	void pause();
	void pauseCheck(int logY);
	void printTime(int x, int y) const;
	void printTextDescription(int x, int y, const char* text) const;
	void printLives(int x, int y) const;
	void gameMetadata(SpaceShip ship) const;
	void deadHeartHandler();
	bool isDie();
	bool timeoutHandler() const;
	void drawIcon(SpaceShip ship) const;
	void deleteIcon(SpaceShip ship) const;
	bool bulkSmash();
	char moveShip(bool& isStart, bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove, char curShipswitchKey, char otherShipSwitchKey);
	void checkVictory(SpaceShip& ship);
	void switchShip(bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove);
};

