#pragma once
#include <iostream>
#include <conio.h>
#include "Spaceship.h"
#include "io_utils.h"
#include "Board.h"
#include "GameStatus.h"

#define GAME_SPEED 200
#define TIME_TO_PAUSE 1000
#define NO_DIRECTION -1
#define BIG_SWITCH_KEY 'B'
#define SMALL_SWITCH_KEY 'S'
#define COLORFUL 1
#define BLACK_WHITE 2
#define TIME_LEN 5
#define NUM_OF_SCREENS 3
#define METADATA_LOG_SIZE 15
#define MAX_LINE 50
#define FILE_DELIMITER ','

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
	bool isGameFromFile = false;
	ifstream stepsIn;
	ofstream stepsOut;

public:
	//ctors + dtors
	Game() = default;
	Game(const Game& _game) = default;
	Game& operator=(const Game& _game) = default;
	~Game();

	//getters + setters
	void setLives(int _lives);
	int getLives() const;
	bool getIsGameFromFile();
	void setIsGameFromFile(bool _isGameIsFromFile);

	//public methods
	void selectColorMode() const;
	void start();
	void load(bool isSilent);
	int extractParamFieldFromFile(string& line, size_t pos);
	void init();

private:

	//private methods
	void printColorMenu() const;
	void setColorMode() const;
	void printMenu() const;
	void makeSelection();
	void run(char key = 0);
	void showInfo() const;
	void pause();
	void pauseCheck(int logY);
	void printTime(const int x, const int y) const;
	void printTextDescription(const int x, const int y, const std::string text) const;
	void printLives(const int x, const int y) const;
	void gameLegend(const SpaceShip& ship);
	bool isLose();
	bool isSomeShipDie();
	bool timeoutHandler() const;
	char moveShip(bool& isStart, bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove, char curShipswitchKey, char otherShipSwitchKey, char prevKey);
	void checkVictory(SpaceShip* ship);
	void switchShip(bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove);
	void getFileNameFromUser();
	void printPlayingShip(const int x, const int y, const SpaceShip& ship) const;
	void printPlayingBoardName(const int x, const int y, string fileName) const;
	void generateSavingFile(ofstream& out);
	void updateFiles();
	char handleKey();
	void handleFileInStaticMode(bool& isOnMoving, SpaceShip& shipToMove, char& prevKey);
};


