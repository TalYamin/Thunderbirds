#include "Board.h"


/*
This function is used to initialize board.
Funtion creats matrix of points according to string which contains board draw.
Then function calls to initBlocks() and initShips() functions.
*/
void Board::initBoard()
{
	timeRemains = MAX_TIME;
	size_t boardLen;
	int y = 0;
	int x = 0;
	const char* boardData = R""""(++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++                          +                       +                     +
+                                +                       +                     +
+++++++                          +                       +                     +
+                                +                       +                     +
+      +                         +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                                        +                     +
+                                                        +                     +
+                                +++++++++               +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +           +++++++++++++                     +
+                                +                                             +
+                                +                                             +
+                                +    ++++++++++++++++++++                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
+                                +                       +                     +
++++++++++++++++++++++++++++++++++++++++++    ++++++++++++++++++++++++++++++++++)"""";
	boardLen = strlen(boardData);
	for (int i = 0; i < boardLen; i++)
	{
		if (boardData[i] == '\n') {
			y++;
			x = 0;
		}
		else
		{
			int objectId = CheckObjectId(boardData[i]);
			Point* point = new Point(x, y, boardData[i], Color::WHITE, objectId);
			setMatrixPoint(x, y, point);
			delete point;
			x++;
		}
	}
	initBlocks();
	initShips();
	initGhosts();
}

/*
This function is used to check the objectId according to char type from board string.
*/
int Board::CheckObjectId(const char& ch) const {
	return ch == (char)BoardFigure::EMPTY ? (int)ObjectId::EMPTY : (int)ObjectId::WALL;

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
	for (int i = 0; i < blocksAmount; i++)
	{
		Block* block = allBlocks[i];
		needToFall = true;
		for (int j = 0; j < block->getSize(); j++) {

			if (!isBlockPointsNoFloor(block->getListPoints()[j]->getX(), block->getListPoints()[j]->getY() + 1, block->getblockId(), &shipInvolved, isWallAlsoInvolved))
			{
				needToFall = false;
			}
		}
		for (size_t m = 0; m < shipInvolved.size(); m++)
		{
			if (shipInvolved[m]->getMaxCarringBlockSize() < block->getSize() && !isWallAlsoInvolved)
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
bool Board::isNotEmptyPoint(int x, int y, const int& direction, vector<Block*>& blocksInvolve, const int& maxCarringBlockSize) {

	if (x >= HORIZONTAL_SIZE || y >= VERTICAL_SIZE) {
		return false;
	}
	else if (mat[x][y].getFigure() == (char)BoardFigure::EMPTY) {
		return false;
	}
	else if (mat[x][y].getFigure() == (char)BoardFigure::BLOCK)
	{
		int BlockId = mat[x][y].getObjecId();
		Block* block = getBlockById(BlockId);

		if ((direction == 2 || direction == 3) && isBlockCanMove(block, direction, blocksInvolve, maxCarringBlockSize))
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
	int blockSize = block->getSize();
	if (blockSize > maxCarringBlockSize)
	{
		return false;
	}
	if (direction == 2)//LEFT
	{
		for (int i = 0; i < blockSize; i++)
		{
			Point* point = block->getListPoints()[i];
			if (isInvalidPlace(point->getX() - 1, point->getY(), block, direction, blocksInvolve, maxCarringBlockSize))
				return false;
		}
	}
	else if (direction == 3)//RIGHT
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
			blocksSum += blocksInvolve[i]->getSize();
		}
		blocksSum += anotherBlock->getSize();
		if (blocksSum <= maxCarringBlockSize) {
			switch (direction)
			{
			case 2: // LEFT
				if (!isNotEmptyPoint(x - 1, y, direction, blocksInvolve, maxCarringBlockSize)) {
					if (find(blocksInvolve.begin(), blocksInvolve.end(), anotherBlock) == blocksInvolve.end()) {
						blocksInvolve.push_back(anotherBlock);
					}
					return true;
				}
				else {
					return false;
				}
				break;
			case 3:// RIGHT
				if (!isNotEmptyPoint(x + 1, y, direction, blocksInvolve, maxCarringBlockSize)) {
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


/*
This function is used to initialize blocks.
*/
void Board::initBlocks()
{
	blocksAmount = 0;
	int firstBlockSize = 1;
	int secondBlockSize = 4;
	int thiredBlockSize = 3;


	Point* block1Point1 = new Point(5, 2, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);

	Point* blockList1[] = { block1Point1 };
	Block* block1 = new Block(blockList1, firstBlockSize, blocksAmount);

	insertNewBlock(block1);

	Point* block2Point1 = new Point(35, 9, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block2Point2 = new Point(36, 9, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block2Point3 = new Point(35, 10, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block2Point4 = new Point(36, 10, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);


	Point* blockList2[] = { block2Point1,block2Point2,block2Point3,block2Point4 };
	Block* block2 = new Block(blockList2, secondBlockSize, blocksAmount);
	insertNewBlock(block2);

	Point* block3Point1 = new Point(55, 18, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block3Point2 = new Point(56, 18, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);
	Point* block3Point3 = new Point(57, 18, (char)BoardFigure::BLOCK, Color::RED, blocksAmount);

	Point* blockList3[] = { block3Point1,block3Point2,block3Point3 };
	Block* block3 = new Block(blockList3, thiredBlockSize, blocksAmount);
	insertNewBlock(block3);

	placeBlocksOnBoard();

}

/*
This function is used to place blocks on board.
For any block, passing on block points and set them as matrix point on board.
*/
void Board::placeBlocksOnBoard()
{
	int blockSize;
	Block* block;
	for (int i = 0; i < blocksAmount; i++)
	{
		block = allBlocks[i];
		blockSize = block->getSize();
		for (int j = 0; j < blockSize; j++)
		{
			Point* blockPoint = block->getListPoints()[j];
			setMatrixPoint(blockPoint->getX(), blockPoint->getY(), blockPoint);
		}
	}
}

/*
This function is used to initialize ships.
*/
void Board::initShips()
{
	bigShip = new SpaceShip(2, 2, '#', Color::GREEN, BIG_SHIP_CARRING_SIZE, ShipSize::BIG);
	bigShip->setupShipMat();
	bigShip->setArrowKeys("wxad");


	smallShip = new SpaceShip(1, 2, '@', Color::BLUE, SMALL_SHIP_CARRING_SIZE, ShipSize::SMALL);
	smallShip->setupShipMat();
	smallShip->setArrowKeys("wxad");

	placeShipsOnBoard(bigShip);
	placeShipsOnBoard(smallShip);
}

/*
This function is used to place ships on board, big ship or smalll ship
 Passing on ship matrix points and set them as matrix point on board.
*/
void Board::placeShipsOnBoard(SpaceShip* ship)
{
	int shipVerticaSize = ship->getVerticalSize();
	int shipHorizontalSize = ship->getHorizontalSize();
	for (int i = 0; i < shipVerticaSize; i++)
	{
		for (int j = 0; j < shipHorizontalSize; j++) {
			setMatrixPoint(ship->getShipMat()[i][j].getX(), ship->getShipMat()[i][j].getY(), &(ship->getShipMat()[i][j]));
		}
	}
}

void Board::initGhosts() {

	Point* ghostPoint1 = new Point(1, 19);
	Point* ghostPoint2 = new Point(78, 21);
	allGhosts.push_back(Ghost(ghostPoint1));
	allGhosts.push_back(Ghost(ghostPoint2));

	placeGhostsOnBoard();
}

void Board::moveGhosts() {

	for (int i = 0; i < allGhosts.size(); i++) {
		allGhosts[i].Move(this);
	}

}

void Board::placeGhostsOnBoard(){

	for (int i = 0; i < allGhosts.size(); i++){
		setMatrixPoint(allGhosts[i].point->getX(), allGhosts[i].point->getY(), allGhosts[i].point);
	}

}


/*
This function is used to insert new block to blocks array
*/
void Board::insertNewBlock(Block* block)
{
	blocksAmount++;

	allBlocks[blocksAmount - 1] = block;
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
	if (y == EXIT_Y && (x == EXIT_X1 || x == EXIT_X2 || x == EXIT_X3)) {
		removeShipFromBoard(ship);
		return true;
	}
	else {
		return false;
	}
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
	for (int i = 0; i < blocksAmount; i++) {
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

	for (int i = 0; i < blocksAmount; i++){
		delete allBlocks[i];
	}

	delete bigShip;
	delete smallShip;
}


