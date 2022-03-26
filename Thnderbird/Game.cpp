#include "Game.h"

using namespace std;


void Game::start() {

	printMenu();
	makeSelection();
}

void Game::setLives(int _lives)
{
	lives = _lives;
}

int Game::getLives()
{
	return lives;
}

void Game::printMenu() {

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

	//	cout << "Game is running !" << endl;
	char key = 0;
	int dir;
	bool isBigMove = true;
	bool isOnMoving = true;
	bool isBigStart = false;
	bool isSmallStart = false;
	do {
		if (isBigMove) {
			if (_kbhit())
			{

				isBigStart = true;
				key = _getch();
				if (key == 's' || key == 'S') {
					deleteIcon(bigShip);
					drawIcon(smallShip);
					isBigMove = false;
				}
				else if (key == 'b' || key == 'B') {
					isOnMoving = !isOnMoving;
				}
				else {
					if ((dir = bigShip.getDirection(key)) != -1)
						bigShip.setDirection(dir);
					else if ((dir = bigShip.getDirection(key)) != -1)
						bigShip.setDirection(dir);
				}
			}
			if (isOnMoving && isBigStart) {
				bigShip.move(bigShip.getType(), &playingBoard);
				Sleep(200);
				playingBoard.timeDown();
				printTime(TIME_X, TIME_Y);
			}
		}
		if (!isBigMove) // is small move
		{
			if (_kbhit())
			{

				isSmallStart = true;
				key = _getch();
				if (key == 'b' || key == 'B') {
					isBigMove = true;
					deleteIcon(smallShip);
					drawIcon(bigShip);
				}
				else if (key == 's' || key == 'S') {
					isOnMoving = !isOnMoving;
				}
				else {
					if ((dir = smallShip.getDirection(key)) != -1)
						smallShip.setDirection(dir);
					else if ((dir = smallShip.getDirection(key)) != -1)
						smallShip.setDirection(dir);
				}
			}
			if (isOnMoving && isSmallStart)
			{
				smallShip.move(smallShip.getType(), &playingBoard);
				Sleep(200);
				playingBoard.timeDown();
				printTime(TIME_X, TIME_Y);
			}
		}
	} while (key != (int)GameStatus::ESC && !isDie());
	pause();
	//should be handle ship movement too 
}


void Game::showInfo() {
	cout << "Instructions are here !" << endl;
}

void Game::init() {
	cout << "Game is initialized !" << endl;
	clear_screen();
	//TODO: Move to Board
	bigShip = SpaceShip(2, 2, '#', Color::GREEN);
	bigShip.setType(2);
	bigShip.setMat(bigShip.getType());
	bigShip.setArrowKeys("wxad");

	playingBoard.initBoard();
	playingBoard.draw();

	gameMetadata(bigShip);

	smallShip = SpaceShip(1, 2, '@', Color::BLUE);
	smallShip.setType(1);
	smallShip.setMat(smallShip.getType());
	smallShip.setArrowKeys("wxad");

	smallShip.initDraw(smallShip.getType());
	bigShip.initDraw(bigShip.getType());

}

void Game::pause() {
	char ch;
	int logY = LOG_Y;
	gotoxy(LOG_X, logY);
	if (gameStatus == GameStatus::DIE)
	{
		lives--;
		setTextColor(Color::YELLOW);
		cout << "You dead " << endl;
		gotoxy(LOG_X, ++logY);
		if (lives > 0)
		{
			cout << "You have " << lives << " more lives! " << endl;
			Sleep(500);
		}
		else {
			cout << "Game Over, Try your luck next time :)" << endl;
			gameStatus = GameStatus::GAMEOVER;

		}
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

void Game::printTime(int x, int y)
{
	setTextColor(Color::MAGENTA);
	gotoxy(x, y);
	for (int i = 0;i < 5;i++)
	{
		cout << ' ';
	}
	gotoxy(x, y);
	cout << playingBoard.getTimeRemains() << endl;
}
void Game::printTextDescription(int x, int y, const char* text)
{
	setTextColor(Color::WHITE);
	gotoxy(x, y);
	cout << text;
}


void Game::printLives(int x, int y)
{
	setTextColor(Color::RED);
	gotoxy(x, y);
	for (int i = 0;i < lives;i++)
	{
		cout << ' ';
	}
	gotoxy(x, y);
	for (int i = 0;i < lives;i++)
		cout << "<3";
}


void Game::gameMetadata(SpaceShip ship)
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

bool Game::isDie()
{
	if (timeoutHandler()) {
		gameStatus = GameStatus::DIE;
		return true;
	}
	if (bulkSmash()) {
		gameStatus = GameStatus::DIE;
		return true;
	}
	return false;
}


bool Game::timeoutHandler()
{
	return playingBoard.getTimeRemains() <= 0;
}

void Game::drawIcon(SpaceShip ship)
{
	printTextDescription(SHIP_ICON_X - SPACE_BETWEEN_METADATA, SHIP_ICON_Y, "playing ship is: ");
	setTextColor(ship.getColor());
	for (int j = 0;j < ship.getVerticalSize(); j++)
	{
		for (int i = 0;i < ship.getHorizontalSize();i++)
		{
			gotoxy(SHIP_ICON_X + i, SHIP_ICON_Y + j);
			cout << ship.getFigure();
		}
	}
}

void Game::deleteIcon(SpaceShip ship)
{
	for (int j = 0;j < ship.getVerticalSize(); j++)
	{
		for (int i = 0;i < ship.getHorizontalSize();i++)
		{
			gotoxy(SHIP_ICON_X + i, SHIP_ICON_Y + j);
			cout << ' ';
		}
	}
}

bool Game::bulkSmash()
{
	return false;
}
