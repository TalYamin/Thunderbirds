#pragma once
#include <iostream>
#include <conio.h>
#include "Spaceship.h"
#include "io_utils.h"
#include "Board.h"
#include "GameStatus.h"
#include "GameSpeedModes.h"

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
#define STAY_KEY 'p'
#define GHOST_DELIMITER_SYMBOL ' '
#define FINISH_KEY 'F'
#define DIE_KEY 'D'


extern bool isBlackAndWhite;
extern bool isSilent;

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
	bool isSilentTestPass = true;
	int lives = 3;
	int numOfScreens = NUM_OF_SCREENS;
	int numOfWins = 0;
	bool isGameFromFile = false;
	bool isSaveMode = false;
	ifstream stepsIn;
	ofstream stepsOut;
	ifstream resultIn;
	ofstream resultOut;
	int gameSpeed = (int)GameSpeedMode::SAVE_SPEED;

public:
	//ctors + dtors
	Game() = default;
	Game(const Game& _game) = default;
	Game& operator=(const Game& _game) = default;
	~Game();

	//getters + setters
	void setGameSpeed(int _speed);
	int getGameSpeed() const;	
	void setLives(int _lives);
	int getLives() const;
	bool getIsGameFromFile();
	void setIsGameFromFile(bool _isGameIsFromFile);
	bool getIsSaveMode();
	void setIsSaveMode(bool _isSaveMode);
	void setIsSilent(bool _s);
	bool getIsSilentTestPass();
	void setIsSilentTestPass(bool _isTestPass);

	//public methods
	void selectColorMode() const;
	void start();
	void load();
	int extractParamFieldFromFile(string& line, size_t pos);
	void init();
	void handleFilesOnInit();
	void printSilentTestResult();

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
	void inferGhostMovement(string& line, const size_t& pos);
	void handleFileInStaticMode(bool& isOnMoving, SpaceShip& shipToMove, char& prevKey);
	void closeFiles();
	bool isValidSilentTest(char requiredKey);
	long inferTimeFromResFile(string& line);
};


