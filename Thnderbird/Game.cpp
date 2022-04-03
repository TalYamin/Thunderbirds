#include "Game.h"
using namespace std;



Game::~Game() {
}

void Game::selectColorMode() const {
	printColorMenu();
	setColorMode();
	clear_screen();
}

void Game::start() {

	printMenu();
	makeSelection();
}

void Game::setLives(int _lives)
{
	lives = _lives;
}

int Game::getLives() const
{
	return lives;
}

void Game::printColorMenu() const {
	cout << "Select your color mode:" << endl;
	cout << "(1) Colorful" << endl;
	cout << "(2) Black and White" << endl;
}

void Game::setColorMode() const {

	int userInput;
	cin >> userInput;
	switch (userInput)
	{
	case COLORFUL:
		isBlackAndWhite = false;
		break;
	case BLACK_WHITE:
		isBlackAndWhite = true;
		break;
	default:
		cout << "Wrong input, please try again !" << endl << endl;
		selectColorMode();
		break;
	}
}

void Game::printMenu() const {

	cout << "Welcome to Thunderbirds !" << endl;
	cout << "Please make a selection:" << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

}


void Game::makeSelection() {
	int userInput;
	cin >> userInput;
	userSelection = static_cast<GameStatus>(userInput);
	switch (userSelection)
	{
	case GameStatus::INFO:
		showInfo();
		system("pause");
		clear_screen();
		start();
		break;
	case GameStatus::START:
		init();
		run();
	case GameStatus::EXIT:
		setTextColor(Color::DARKGREY);
		cout << "Goodbye !" << endl;
		break;
	default:
		cout << "Wrong input, please try again !" << endl << endl;
		start();
		break;
	}

}


void Game::run() {

	char key = 0;
	SpaceShip* bigShip = playingBoard.getBigShip();
	SpaceShip* smallShip = playingBoard.getSmallShip(); 
	do {
		if (isBigMove && !bigShip->getIsExit()) {
			key = moveShip(isBigStart, isBigOnMoving, *smallShip, *bigShip, BIG_SWITCH_KEY, SMALL_SWITCH_KEY);
			checkVictory(bigShip);
			if (bigShip->getIsExit() && gameStatus != GameStatus::VICTORY) {
				switchShip(isBigOnMoving, *smallShip, *bigShip);
			}
		}
		if (!isBigMove && !smallShip->getIsExit()) { // is small move
			key = moveShip(isSmallStart, isSmallOnMoving, *bigShip, *smallShip, SMALL_SWITCH_KEY, BIG_SWITCH_KEY);
			checkVictory(smallShip);
			if (smallShip->getIsExit() && gameStatus != GameStatus::VICTORY) {
				switchShip(isSmallOnMoving, *bigShip, *smallShip);
			}
		}
	} while (key != (int)GameStatus::ESC && !isLose() && gameStatus != GameStatus::VICTORY);
	pause();
}

char Game::moveShip(bool& isStart, bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove, char curShipswitchKey, char otherShipSwitchKey) {
	char key = 0;
	int dir;
	if (_kbhit())
	{

		isStart = true;
		key = _getch();
		if (key == tolower(otherShipSwitchKey) || key == toupper(otherShipSwitchKey)) {
			if (shipToSwitch.getIsExit() == false)
			{
				switchShip(isOnMoving, shipToSwitch, shipToMove);
			}
		}
		else if (key == tolower(curShipswitchKey) || key == toupper(curShipswitchKey)) {
			isOnMoving = !isOnMoving;
		}
		else if ((dir = shipToMove.getDirection(key)) != NO_DIRECTION) {
			isOnMoving = true;
			shipToMove.setDirection(dir);
		}
	}
	if (isOnMoving && isStart) {
		shipToMove.move(&playingBoard);
		playingBoard.fallBlocksIfNoFloor();
		Sleep(GAME_SPEED);
		playingBoard.timeDown();
		printTime(TIME_X, TIME_Y);
	}
	return key;
}

void Game::switchShip(bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove) {
	isBigMove = !isBigMove;
	isOnMoving = true;
	deleteIcon(shipToMove);
	drawIcon(shipToSwitch);
	shipToMove.setDirection(NO_DIRECTION);
}

void Game::showInfo() const {
	setTextColor(Color::YELLOW);
	cout << endl;
	cout << "Instructions: " << endl;
	setTextColor(Color::WHITE);
	cout << "Two 'ships' are trapped inside an ancient Egyptian tomb." << endl << "A big one and a small one." << endl << "The big ship can move or carry blocks of total size 6." << endl << "The small ship can move or carry blocks of total size 2." << endl << "You should make them reaching the exit point in time." << endl << endl;
	setTextColor(Color::YELLOW);
	cout << "Arrow Keys: " << endl;
	setTextColor(Color::WHITE);
	cout << "LEFT:  a or A " << endl;
	cout << "RIGHT: d or D " << endl;
	cout << "UP:    w or W " << endl;
	cout << "DOWN:  x or X " << endl << endl;
	setTextColor(Color::YELLOW);
	cout << "Switch keys:" << endl;
	cout << "(If we were with the this ship already, just STOP the movement of this ship)" << endl;
	setTextColor(Color::WHITE);
	cout << "Switched to the Big Ship:   b or B " << endl;
	cout << "Switched to the Small Ship: s or S " << endl << endl;
}

void Game::init() {
	clear_screen();
	playingBoard.initBoard();
	playingBoard.draw();

	gameMetadata(*(playingBoard.getBigShip()));
}

void Game::pause() {
	char ch;
	int logY = LOG_Y;
	gotoxy(LOG_X, logY);
	if (gameStatus == GameStatus::DIE)
	{
		lives--;
		isBigMove = true;
		setTextColor(Color::YELLOW);
		cout << "You dead " << endl;
		gotoxy(LOG_X, ++logY);
		if (lives > 0)
		{
			cout << "You have " << lives << " more lives! " << endl;
			Sleep(TIME_TO_PAUSE);
		}
		else {
			cout << "Game Over, Try your luck next time :)" << endl;
			gameStatus = GameStatus::GAMEOVER;

		}
		gotoxy(LOG_X, ++logY);
	}
	else if (gameStatus == GameStatus::VICTORY) {
		setTextColor(Color::YELLOW);
		cout << "You win !" << endl;
		gotoxy(LOG_X, ++logY);
	}
	else
	{
		setTextColor(Color::LIGHTBLUE);
		cout << "Game paused ";
	}
	pauseCheck(logY);
}

void Game::pauseCheck(int logY)
{
	char ch;
	switch (gameStatus)
	{
	case GameStatus::GAMEOVER:
	{
		gameStatus = GameStatus::PAUSE_EXIT;
		break;
	}
	case GameStatus::VICTORY:
		gameStatus = GameStatus::PAUSE_EXIT;
		break;
	default:
	{
		cout << "press ESC to continue or 9 to Exit" << endl;
		do {
			ch = _getch();
		} while (ch != (int)GameStatus::ESC && ch != (int)GameStatus::PAUSE_EXIT);
		if (ch == (int)GameStatus::ESC) {
			claer_line(logY);
			setTextColor(Color::WHITE);
			if (gameStatus == GameStatus::DIE)
			{
				init();
			}
			gameStatus = GameStatus::RUNNING;
			isBigOnMoving = false;
			isSmallOnMoving = false;
			run();

		}
		else if (ch == (int)GameStatus::PAUSE_EXIT) {
			setTextColor(Color::DARKGREY);
			gotoxy(LOG_X, ++logY);
			userSelection = GameStatus::EXIT;
		}
	}
	}
}

void Game::printTime(int x, int y) const
{
	setTextColor(Color::MAGENTA);
	gotoxy(x, y);
	for (int i = 0; i < TIME_LEN; i++)
	{
		cout << ' ';
	}
	gotoxy(x, y);
	cout << playingBoard.getTimeRemains() << endl;
}
void Game::printTextDescription(int x, int y, const char* text) const
{
	setTextColor(Color::WHITE);
	gotoxy(x, y);
	cout << text;
}


void Game::printLives(int x, int y) const
{
	setTextColor(Color::RED);
	gotoxy(x, y);
	for (int i = 0; i < lives; i++)
	{
		cout << ' ';
	}
	gotoxy(x, y);
	for (int i = 0; i < lives; i++)
		cout << "<3";
}


void Game::gameMetadata(SpaceShip ship) const
{
	printTextDescription(LIVES_X - SPACE_BETWEEN_METADATA, LIVES_Y, "Lives Remains: ");
	printLives(LIVES_X, LIVES_Y);
	printTextDescription(TIME_X - SPACE_BETWEEN_METADATA, TIME_Y, "Time Remains: ");
	printTime(TIME_X, TIME_Y);
	drawIcon(ship);
}

//Delete heart in case of dead
void Game::deadHeartHandler()
{
	int heartIndexToDelete = LIVES_X + ((lives - 1) * 2);
	gotoxy(heartIndexToDelete, LIVES_Y);
	cout << "  ";
	lives--;
}

bool Game::isLose()
{
	if (timeoutHandler()) {
		gameStatus = GameStatus::DIE;
		return true;
	}
	if (isSomeShipDie()) {
		gameStatus = GameStatus::DIE;
		return true;
	}
	return false;
}

bool Game::isSomeShipDie()
{
	return (playingBoard.getBigShip()->getIsDie() == true || playingBoard.getSmallShip()->getIsDie() == true);
}

bool Game::timeoutHandler() const
{
	return playingBoard.getTimeRemains() <= 0;
}

void Game::drawIcon(SpaceShip ship) const
{
	printTextDescription(SHIP_ICON_X - SPACE_BETWEEN_METADATA, SHIP_ICON_Y, "playing ship is: ");
	for (int j = 0;j < ship.getVerticalSize(); j++)
	{
		for (int i = 0; i < ship.getHorizontalSize(); i++)
		{
			gotoxy(SHIP_ICON_X + i, SHIP_ICON_Y + j);
			setTextColor(ship.getColor());
			cout << ship.getFigure();
		}
	}
}

void Game::deleteIcon(SpaceShip ship) const
{
	for (int j = 0; j < ship.getVerticalSize(); j++)
	{
		for (int i = 0; i < ship.getHorizontalSize(); i++)
		{
			gotoxy(SHIP_ICON_X + i, SHIP_ICON_Y + j);
			cout << ' ';
		}
	}
}


void Game::checkVictory(SpaceShip* ship) {

	if (!ship->getIsExit()) {
		ship->setIsExit(playingBoard.checkExit(ship));
	}
	if (playingBoard.getBigShip()->getIsExit() == true && playingBoard.getSmallShip()->getIsExit() == true) {
		gameStatus = GameStatus::VICTORY;
	}
}