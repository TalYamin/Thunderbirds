#pragma once
#define HORIZONTAL_SIZE 80
#define VERTICAL_SIZE 23
#define VERTICAL_GAME_DIMENSION_SIZE 25
#define LIVES_X 1
#define SHIP_ICON_Y 31
#define SPACE_BETWEEN_METADATA 20
#define LOG_X 0
#define LOG_Y 24
#define BLOCKS_AMOUNT 3
#define BIG_SHIP_CARRING_SIZE 6
#define SMALL_SHIP_CARRING_SIZE 2
#define FILE_PREFIX "tb_"
#define FILE_EXTENSION ".screen"
#define FIRST_BOARD_SUFFIX 'a'


#include "Point.h"
#include "Block.h"
#include "BoardFigure.h"
#include "Spaceship.h"
#include "ObjectId.h"
#include "Ghost.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class SpaceShip;
class Block;
class Point;
class Ghost;

class Board
{
	//data members
	Point mat[HORIZONTAL_SIZE][VERTICAL_SIZE];
	int maxHorizontalSize = HORIZONTAL_SIZE;
	int maxVerticalSize = VERTICAL_SIZE;
	long timeRemains = 1;
	vector <Block*> allBlocks;
	vector <Ghost*> allGhosts;
	SpaceShip* smallShip = {};
	SpaceShip* bigShip = {};
	int shipsAmount = 2;
	bool isBigShipInitialized = false;
	bool isSmallShipInitialized = false;
	vector<Point*> exitPoints;
	char currFileSuffix = FIRST_BOARD_SUFFIX;
	bool isFileLoadFail = false;
	string playingFileName;
	int timeIndexPlace = 0;
	int liveIndexPlace = 0;
	int shipIndexPlace = 0;
	int boardNameIndexPlace = 0;
	int legendXIndexPlace = 0;
	int legendYIndexPlace = 0;


public:

	//ctors + dtors
	Board() = default;
	Board(int _maxHorizontalSize, int _maxVerticalSize, long _timeRemains, SpaceShip* _smallShip, SpaceShip* bigShip);
	Board(const Board& _board) = default;
	Board& operator=(const Board& _board) = default;
	~Board();


	//getters + setters
	void setMaxHorizontalSize(int _horizontal);
	int getMaxHorizontalSize() const;
	void setGetMaxVerticalSize(int _vertical);
	int getMaxVerticalSize() const;
	void setTimeRemains(long timeToSet);;
	long getTimeRemains() const;
	Point(*getMat())[VERTICAL_SIZE];
	int getShipsAmount() const;
	SpaceShip* getBigShip() const;
	SpaceShip* getSmallShip() const;
	vector <Ghost*> getAllGhosts() const;
	vector<Point*> getExitPoints() const;
	char getCurrFileSuffix();
	void setCurrFileSuffix(char _currFileSuffix);
	bool getIsFileLoadFail() const;
	void setPlayingFileName(string _playingFileName);
	string getPlayingFileName();
	void setTimeIndexPlace(int _timeIndexPlace);
	int getTimeIndexPlace() const;
	void setLiveIndexPlace(int _liveIndexPlace);
	int getLiveIndexPlace() const;
	void setShipIndexPlace(int _shpiIndexPlace);
	int getShipIndexPlace() const;
	void setBoardNameIndexPlace(int _boardNameIndexPlace);
	int getBoardNameIndexPlace() const;
	void setLegendYIndexPlace(int _legendYIndexPlace);
	int getLegendYIndexPlace() const;
	void setLegendXIndexPlace(int _legendXIndexPlace);
	int getLegendXIndexPlace() const;

	//public methods
	void updatePlayingBoardName();
	void deleteExistDataFromBoard();
	Block* getBlockById(const int& objectId) const;
	Ghost* getGhostById(const int& objectId) const;
	void removeShipFromBoard(SpaceShip* ship);
	void removeGhostFromBoard(Ghost* ghost);
	bool checkExit(SpaceShip* ship);
	bool isNotEmptyPoint(int x, int y, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize, bool* isGhost);
	void initBoard();
	void timeDown();
	void draw() const;
	bool isBlockCanMove(Block* block, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize);
	void fallBlocksIfNoFloor();
	void moveGhosts();

private:

	//private methods
	bool isBlockPointsNoFloor(const int& x, const int& y, const int& blockId, vector<SpaceShip*>* shipInvolved, bool& isWallAlsoInvolve);
	void initShips();
	void insertNewBlock(Block* block);
	bool isInvalidPlace(int x, int y, Block* block, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize);
	bool canMoveMultipleBlocks(int x, int y, Block* block, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize);
	int initGhost(const int& x, const int& y);
	void loadBoardFromTextFile(string fileName);
	void setPointAndObject(const int& x, const int& y, const char& c);
	void placePointOnBoard(const int& x, const int& y, const char& c, const Color& color, const int& objectId);
	int initBlock(int x, int y, char c);
	Block* checkIsBlockExist(const char& c);
	bool isBlockFigure(const char& c);
	void addExitPoint(Point* point);
	void addAllExitPoints();
	void readTimeRemainForFile(ifstream in);
};



