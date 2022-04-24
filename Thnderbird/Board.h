#pragma once
#define HORIZONTAL_SIZE 80
#define VERTICAL_SIZE 25
#define LIVES_X 1
#define TIME_X 22
#define SHIP_X 42
#define BOARD_NAME_X 62
#define METADATA_LOG_Y 1
#define SHIP_ICON_X 30
#define SHIP_ICON_Y 31
#define SPACE_BETWEEN_METADATA 20
#define LOG_X 30
#define LOG_Y 27
#define EXIT_Y 25
#define EXIT_X1 42
#define EXIT_X2 43
#define EXIT_X3 44
#define BLOCKS_AMOUNT 3
#define MAX_TIME 10000
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
	long timeRemains = MAX_TIME;
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
	Point(*getMat())[25];
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

	//public methods
	void updatePlayingBoardName();
	void deleteExistDataFromBoard();
	Block* getBlockById(const int& objectId) const;
	Ghost* getGhostById(const int& objectId) const;
	void removeShipFromBoard(SpaceShip* ship);
	void removeGhostFromBoard(Ghost* ghost);
	bool checkExit(SpaceShip* ship);
	bool isNotEmptyPoint(int x, int y, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize, bool* isGhost, bool* isWallInvolve);
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
};



