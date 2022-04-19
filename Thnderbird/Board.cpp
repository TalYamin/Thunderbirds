#include "Board.h"


/*
This function is used to initialize board.
Funtion creats matrix of points according to string which contains board draw.
Then function calls to initBlocks() and initShips() functions.
*/
void Board::initBoard()
{
	if (playingFileName.empty()) {
		updatePlayingBoardName();
	}

	timeRemains = MAX_TIME;
	allBlocks.clear();
	allGhosts.clear();
	isBigShipInitialized = false;
	isSmallShipInitialized = false;
	initShips();
	loadBoardFromTextFile(playingFileName);
	if (!isFileLoadFail) {
		addAllExitPoints();

	}
}

void Board::updatePlayingBoardName()
{
	playingFileName += FILE_PREFIX;
	playingFileName += currFileSuffix;
	playingFileName += FILE_EXTENSION;
}


void Board::loadBoardFromTextFile(string fileName)
{
	int y = 0;
	int x = 0;
	ifstream in(fileName);
	char c;

	if (in.is_open()) {
		while (in.good()) {
			in.get(c);
			if (c == '\n') {
				y++;
				x = 0;
			}
			else
			{
				setPointAndObject(x, y, c);
				x++;
			}
		}
	}

	if (!in.eof() && in.fail()) {
		cout << "error reading " << fileName << endl;
		isFileLoadFail = true;
	}

	in.close();
}

void Board::setPointAndObject(const int& x, const int& y, const char& c)
{
	int objectId;
	switch (c)
	{
	case (char)BoardFigure::INFO:
		objectId = (int)ObjectId::INFO;
		placePointOnBoard(x, y, c, Color::WHITE, (int)ObjectId::EMPTY);
		break;
	case (char)BoardFigure::EMPTY:
		objectId = (int)ObjectId::EMPTY;
		placePointOnBoard(x, y, c, Color::WHITE, (int)ObjectId::EMPTY);
		break;
	case (char)BoardFigure::WALL:
		objectId = (int)ObjectId::WALL;
		placePointOnBoard(x, y, c, Color::WHITE, objectId);
		break;
	case (char)BoardFigure::BIG_SHIP:
		if (!isBigShipInitialized) {
			bigShip->setupShipMat(x, y);
			isBigShipInitialized = true;
		}
		objectId = (int)ObjectId::BIG;
		placePointOnBoard(x, y, c, bigShip->getColor(), objectId);
		break;
	case (char)BoardFigure::SMALL_SHIP:
		if (!isSmallShipInitialized) {
			smallShip->setupShipMat(x, y);
			isSmallShipInitialized = true;
		}
		objectId = (int)ObjectId::SMALL;
		placePointOnBoard(x, y, c, smallShip->getColor(), objectId);
		break;
	case (char)BoardFigure::HORIZONTAL_GHOST:
		objectId = initGhost(x, y);
		placePointOnBoard(x, y, c, Color::BROWN, objectId);
		break;
	default:
		if (isBlockFigure(c)) {
			objectId = initBlock(x, y, c);
			placePointOnBoard(x, y, c, Color::RED, objectId);
		}
		break;
	}
}


void Board::placePointOnBoard(const int& x, const int& y, const char& c, const Color& color, const int& objectId) {
	Point* point = new Point(x, y, c, color, objectId);
	setMatrixPoint(x, y, point);
	delete point;
}



/*
This function is used to draw board according to points matrix.
*/
void Board::draw() const
{
	for (int i = 0; i < maxVerticalSize; i++)
	{
		for (int j = 0; j < maxHorizontalSize; j++)
		{
			mat[j][i].draw();
		}
		cout << endl;
	}
	cout << endl;
}

/*
This function i used to set matrix point.
*/
void Board::setMatrixPoint(int _x, int _y, Point* _p)
{
	mat[_x][_y] = *_p;
}

/*
Function is used to make block falling in case there is no floor.
Function go over all blocks on board, and using isBlockPointsNoFloor() function in order to check
that all points of block are able to fall and not blocked. Then, in case there are ships which blocks
are falling on them, so checking if ship can carry it and if not is die.
*/
void Board::fallBlocksIfNoFloor()
{
	bool needToFall;
	bool isWallAlsoInvolved = false;
	vector<SpaceShip*> shipInvolved;
	for (int i = 0; i < allBlocks.size(); i++)
	{
		Block* block = allBlocks[i];
		needToFall = true;
		for (int j = 0; j < block->getListPoints().size(); j++) {

			if (!isBlockPointsNoFloor(block->getListPoints()[j]->getX(), block->getListPoints()[j]->getY() + 1, block->getblockId(), &shipInvolved, isWallAlsoInvolved))
			{
				needToFall = false;
			}
		}
		for (size_t m = 0; m < shipInvolved.size(); m++)
		{
			if (shipInvolved[m]->getMaxCarringBlockSize() < block->getListPoints().size() && !isWallAlsoInvolved)
			{
				shipInvolved[m]->setIsDie(true);
				return;
			}
		}
		if (needToFall == true)
		{
			block->fall(this);
		}
		isWallAlsoInvolved = false;
	}
}

/*
Function receives x and y valuse and block id.
This function is used to check per point of block, if the point is not blocked by other entities on
board and in case point is blocked, to notify that the block can not fall.
Function checking walls which invloved and other ships and returns the infromation in output
parameters.
*/
bool Board::isBlockPointsNoFloor(const int& x, const int& y, const int& blockId, vector<SpaceShip*>* shipInvolved, bool& isWallAlsoInvolve) {
	Point point = mat[x][y];
	if (point.getObjecId() == (int)ObjectId::EMPTY || point.getObjecId() == blockId)
		return true;
	if (point.getObjecId() == (int)ObjectId::WALL)
		isWallAlsoInvolve = true;
	if (point.getObjecId() == (int)ObjectId::SMALL)
	{
		if (find((*shipInvolved).begin(), (*shipInvolved).end(), smallShip) == (*shipInvolved).end())
			(*shipInvolved).push_back(smallShip);
	}
	if (point.getObjecId() == (int)ObjectId::BIG)
	{
		if (find((*shipInvolved).begin(), (*shipInvolved).end(), bigShip) == (*shipInvolved).end())
			(*shipInvolved).push_back(bigShip);
	}
	return false;
}

/*
This function is used to check if point is not empty.
Checking the figure on board matrix. In case of block, calling to isBlockCanMove() function which
should check if the the block is able to move or block this point.
*/
bool Board::isNotEmptyPoint(int x, int y, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize, bool* isGhost) {

	if (mat[x][y].getFigure() == (char)BoardFigure::HORIZONTAL_GHOST) {
		*isGhost = true;
	}

	if (x >= HORIZONTAL_SIZE || y >= VERTICAL_SIZE) {
		return false;
	}
	else if (mat[x][y].getFigure() == (char)BoardFigure::EMPTY) {
		return false;
	}
	else if (isBlockFigure(mat[x][y].getFigure()))
	{
		int BlockId = mat[x][y].getObjecId();
		Block* block = getBlockById(BlockId);

		if ((direction == (int)Direction::LEFT || direction == (int)Direction::RIGHT) && isBlockCanMove(block, direction, blocksInvolve, maxCarringBlockSize))
		{
			if (find(blocksInvolve.begin(), blocksInvolve.end(), block) == blocksInvolve.end())
				blocksInvolve.push_back(block);
			return false;
		}
	}

	return true;
}

/*
This function is used to check if block can move.
Accoriding to block size, checking if it is not excceded the max carring block size of ship.
Then, passing on any point of block and checking the next index according to direction and checking
if it is invalid place.
*/
bool Board::isBlockCanMove(Block* block, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize) {
	int blockSize = block->getListPoints().size();
	if (blockSize > maxCarringBlockSize)
	{
		return false;
	}
	if (direction == (int)Direction::LEFT)
	{
		for (int i = 0; i < blockSize; i++)
		{
			Point* point = block->getListPoints()[i];
			if (isInvalidPlace(point->getX() - 1, point->getY(), block, direction, blocksInvolve, maxCarringBlockSize))
				return false;
		}
	}
	else if (direction == (int)Direction::RIGHT)
	{
		for (int i = 0; i < blockSize; i++)
		{
			Point* point = block->getListPoints()[i];
			if (isInvalidPlace(point->getX() + 1, point->getY(), block, direction, blocksInvolve, maxCarringBlockSize)) {
				return false;
			}
		}
	}
	return true;
}

/*
This fucntion is used to check if point of block is going to invalid place.
In case of wall or ship, it returns true for invalid place. In case of block, function calls to
canMoveMultipleBlocks() function in order to check if multiple block push is available or this point
is blocked by another block.
*/
bool Board::isInvalidPlace(int x, int y, Block* block, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize) {

	bool canMoveMultiBlocks = true;
	int currObejctId = mat[x][y].getObjecId();

	if (currObejctId == (int)ObjectId::WALL || currObejctId == (int)ObjectId::BIG || currObejctId == (int)ObjectId::SMALL) {
		return true;
	}
	else if (currObejctId != (int)ObjectId::EMPTY) {
		canMoveMultiBlocks = canMoveMultipleBlocks(x, y, block, direction, blocksInvolve, maxCarringBlockSize);
	}

	return  (mat[x][y].getObjecId() != (int)ObjectId::EMPTY && !canMoveMultiBlocks);
}


/*
This function is used to check if ship can move multiple blocks in parallel, depending on
max carring block size. Function recognize the blocks which involved and checks its id.
If they have different ids, there is calculation of blocks sum and checking it with max carring size.
Then, there is another call for isNotEmptyPoint() funtion to check the next block in blocks chain,
according to direction. In case, one of blocks can't be move or the size of block is exceeded the
max size- return false. else, return true.
*/
bool Board::canMoveMultipleBlocks(int x, int y, Block* block, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize) {

	int blocksSum = 0;
	Block* anotherBlock = getBlockById(mat[x][y].getObjecId());

	if (anotherBlock->getblockId() != block->getblockId()) {
		for (size_t i = 0; i < blocksInvolve.size(); i++) {
			blocksSum += blocksInvolve[i]->getListPoints().size();
		}
		blocksSum += anotherBlock->getListPoints().size();
		if (blocksSum <= maxCarringBlockSize) {
			switch (direction)
			{
			case (int)Direction::LEFT:
				if (!isNotEmptyPoint(x - 1, y, direction, blocksInvolve, maxCarringBlockSize, nullptr)) {
					if (find(blocksInvolve.begin(), blocksInvolve.end(), anotherBlock) == blocksInvolve.end()) {
						blocksInvolve.push_back(anotherBlock);
					}
					return true;
				}
				else {
					return false;
				}
				break;
			case (int)Direction::RIGHT:
				if (!isNotEmptyPoint(x + 1, y, direction, blocksInvolve, maxCarringBlockSize, nullptr)) {
					if (find(blocksInvolve.begin(), blocksInvolve.end(), anotherBlock) == blocksInvolve.end()) {
						blocksInvolve.push_back(anotherBlock);
					}
					return true;
				}
				else {
					return false;
				}
				break;
			default:
				return false;
				break;
			}
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}

}




int Board::initBlock(int x, int y, char c) {

	Block* block;
	Point* blockPoint = new Point(x, y, c, Color::RED);
	block = checkIsBlockExist(c);

	if (block != nullptr) {
		block->addPointToBlock(blockPoint);
	}
	else {
		vector <Point*> blockList;
		blockList.push_back(blockPoint);
		block = new Block(blockList, c);
		insertNewBlock(block);
	}

	return block->getblockId();

}

Block* Board::checkIsBlockExist(const char& c) {

	Block* currBlock;
	vector<Point*> currList;
	for (int i = 0; i < allBlocks.size(); i++) {
		currBlock = allBlocks[i];
		currList = currBlock->getListPoints();
		for (int j = 0; j < currList.size(); j++) {
			if (currList[j]->getFigure() == c) {
				return currBlock;
			}
		}
	}
	return nullptr;
}

bool Board::isBlockFigure(const char& c)
{
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}

void Board::addExitPoint(Point* point)
{
	exitPoints.push_back(point);
}

void Board::addAllExitPoints() {

	for (int i = 0; i < maxHorizontalSize; i++) { //downExit
		if (mat[i][maxVerticalSize - 1].getFigure() == (char)BoardFigure::EMPTY) {
			addExitPoint(&mat[i][maxVerticalSize - 1]);
		}
	}

	for (int j = 0; j < maxVerticalSize; j++) { //rightExit
		if (mat[maxHorizontalSize - 1][j].getFigure() == (char)BoardFigure::EMPTY) {
			addExitPoint(&mat[maxHorizontalSize - 1][j]);
		}
	}

}



/*
This function is used to initialize ships.
*/
void Board::initShips()
{
	bigShip = new SpaceShip(2, 2, (char)BoardFigure::BIG_SHIP, Color::GREEN, BIG_SHIP_CARRING_SIZE, ShipSize::BIG);
	bigShip->setArrowKeys("wxad");


	smallShip = new SpaceShip(1, 2, (char)BoardFigure::SMALL_SHIP, Color::BLUE, SMALL_SHIP_CARRING_SIZE, ShipSize::SMALL);
	smallShip->setArrowKeys("wxad");

}



int Board::initGhost(const int& x, const int& y) {

	int size = 1;

	Point* ghostPoint = new Point(x, y, (char)BoardFigure::HORIZONTAL_GHOST, Color::BROWN);
	Point* ghostList[] = { ghostPoint };
	Ghost* ghost = new Ghost(ghostList, size);

	allGhosts.push_back(ghost);
	return ghost->getId();
}

void Board::moveGhosts() {

	for (int i = 0; i < allGhosts.size(); i++) {
		allGhosts[i]->Move(this);
	}

}


/*
This function is used to insert new block to blocks array
*/
void Board::insertNewBlock(Block* block)
{
	allBlocks.push_back(block);
}

/*
This function is used as constructor of Board.
*/
Board::Board(int _maxHorizontalSize, int _maxVerticalSize, long _timeRemains, SpaceShip* _smallShip, SpaceShip* _bigShip) {
	maxHorizontalSize = _maxHorizontalSize;
	maxVerticalSize = _maxVerticalSize;
	timeRemains = _timeRemains;
	smallShip = _smallShip;
	bigShip = _bigShip;
}

/*
This function is used to check if ship arrived to exit.
In case, it arrived to exit, function calls to removeShipFromBoard() in order
to remove ship from board view.
*/
bool Board::checkExit(SpaceShip* ship) {

	int x = ship->getShipMat()[0][0].getX();
	int y = ship->getShipMat()[0][0].getY();
	for (int i = 0; i < exitPoints.size(); i++) {
		if (exitPoints[i]->getX() == maxHorizontalSize - 1) {
			if (exitPoints[i]->getX() + 1 == x && exitPoints[i]->getY() == y) {
				removeShipFromBoard(ship);
				return true;
			}
		}
		else {
			if (exitPoints[i]->getX() == x && exitPoints[i]->getY() + 1 == y) {
				removeShipFromBoard(ship);
				return true;
			}
		}

	}
	return false;
}

/*
This function is used to remove ship from board view.
Passing on matrix points of board, make them empty and draw spaces on board.
*/
void Board::removeShipFromBoard(SpaceShip* ship) {

	int shipVerticaSize = ship->getVerticalSize();
	int shipHorizontalSize = ship->getHorizontalSize();

	for (int i = 0; i < shipVerticaSize; i++)
	{
		for (int j = 0; j < shipHorizontalSize; j++) {
			ship->getShipMat()[i][j].draw((char)BoardFigure::EMPTY);
			mat[ship->getShipMat()[i][j].getX()][ship->getShipMat()[i][j].getY()].setFigure((char)BoardFigure::EMPTY);
		}
	}
}

/*
This function is used to get block by its id.
*/
Block* Board::getBlockById(const int& objectId) const {
	for (int i = 0; i < allBlocks.size(); i++) {
		if (allBlocks[i]->getblockId() == objectId) {
			return allBlocks[i];
		}
	}
	return nullptr;
}

/*
This is setter function of time remains data member.
*/
void Board::setTimeRemains(long timeToSet) {
	timeRemains = timeToSet;
}

/*
This is getter function of time remains data member.
*/
long Board::getTimeRemains() const {
	return timeRemains;
}

/*
This is getter function of ships amount data member.
*/
int Board::getShipsAmount() const {
	return shipsAmount;
}

/*
This is getter function of big ship data member.
*/
SpaceShip* Board::getBigShip() const {
	return bigShip;
}

/*
This is getter function of small ship data member.
*/
SpaceShip* Board::getSmallShip() const {
	return smallShip;
}

vector<Ghost*> Board::getAllGhosts() const
{
	return allGhosts;
}

vector<Point*> Board::getExitPoints() const
{
	return exitPoints;
}

char Board::getCurrFileSuffix()
{
	return currFileSuffix;
}

void Board::setCurrFileSuffix(char _currFileSuffix)
{
	currFileSuffix = _currFileSuffix;
}

bool Board::getIsFileLoadFail() const
{
	return isFileLoadFail;
}

void Board::setPlayingFileName(string _playingFileName) {

	playingFileName = _playingFileName;

}

string Board::getPlayingFileName()
{
	return playingFileName;
}

/*
This function is used to decrease time.
*/
void Board::timeDown() {
	timeRemains--;
}

/*
This is setter function of max horizontal size data member.
*/
void Board::setMaxHorizontalSize(int _horizontal) {
	maxHorizontalSize = _horizontal;
};

/*
This is getter function of max horizontal size data member.
*/
int Board::getMaxHorizontalSize() const {
	return maxHorizontalSize;
}

/*
This is setter function of max veritcal size data member.
*/
void Board::setGetMaxVerticalSize(int _vertical) {
	maxVerticalSize = _vertical;
}

/*
This is getter function of max veritcal size data member.
*/
int Board::getMaxVerticalSize() const {
	return maxVerticalSize;
}

/*
This is getter function of points matrix data member.
*/
Point(*Board::getMat())[25]{
	return mat;
};

/*
Distruction of Board.
*/
Board::~Board() {

	for (int i = 0; i < allBlocks.size(); i++) {
		delete allBlocks[i];
	}

	delete bigShip;
	delete smallShip;
}


