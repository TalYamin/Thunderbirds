#pragma once
#include <iostream>
#include <conio.h>
#include "Spaceship.h"
#include "io_utils.h"
#include "Board.h"
#include "GameStatus.h"
#define GAME_SPEED 40
#define TIME_TO_PAUSE 500
#define NO_DIRECTION -1
#define BIG_SWITCH_KEY 'B'
#define SMALL_SWITCH_KEY 'S'
#define COLORFUL 1
#define BLACK_WHITE 2
#define TIME_LEN 5
#define NUM_OF_SCREENS 3
#define METADATA_LOG_SIZE 15

extern bool isBlackAndWhite;

class Game
{
	//data members
	GameStatus gameStatus = GameStatus::NO_SELECTION;
	GameStatus userSelection = GameStatus::NO_SELECTION;
	Board playingBoard;
	bool isBigMove = true;
	bool isBigOnMoving = false;
	bool isSmallOnMoving = false;
	bool isBigStart = false;
	bool isSmallStart = false;
	int lives = 3;
	int numOfScreens = NUM_OF_SCREENS;
	int numOfWins = 0;
	int timeIndexPlace = 0;
	int liveIndexPlace = 0;
	int shipIndexPlace = 0;
	int boardNameIndexPlace = 0;

public:
	//ctors + dtors
	Game() = default;
	Game(const Game& _game) = default;
	Game& operator=(const Game& _game) = default;
	~Game();

	//getters + setters
	void setLives(int _lives);
	int getLives() const;
	void setTimeIndexPlace(int _timeIndexPlace);
	int getTimeIndexPlace() const;
	void setLiveIndexPlace(int _liveIndexPlace);
	int getLiveIndexPlace() const;
	void setShipIndexPlace(int _shpiIndexPlace);
	int getShipIndexPlace() const;
	void setBoardNameIndexPlace(int _boardNameIndexPlace);
	int getBoardNameIndexPlace() const;

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
	void printTime(const int x, const int y) const;
	void printTextDescription(const int x, const int y, const std::string text) const;
	void printLives(const int x, const int y) const;
	void gameMetadata(const SpaceShip& ship);
	void makeEmptyMetadataSpaces(const int startXLog, const int topYLog) const;
	void deadHeartHandler();
	bool isLose();
	bool isSomeShipDie();
	bool timeoutHandler() const;
	void drawIcon(const SpaceShip& ship) const;
	void deleteIcon(const SpaceShip& ship) const;
	char moveShip(bool& isStart, bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove, char curShipswitchKey, char otherShipSwitchKey);
	void checkVictory(SpaceShip* ship);
	void switchShip(bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove);
	void getFileNameFromUser();
	void printPlayingShip(const int x, const int y, const SpaceShip& ship) const;
	void printPlayingBoardName(const int x, const int y, string fileName) const;

};


