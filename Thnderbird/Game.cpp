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

	cin >> userSelection;
	switch (userSelection)
	{
	case INFO:
		showInfo();
		break;
	case START:
		init();
		run();
	case EXIT:
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
				bigShip.move(bigShip.getType());
				Sleep(100);
				playingBoard.timeDown();
				printTime(TIME_X, TIME_Y);
			}
		}
		if (!isBigMove)
		{
			if (_kbhit())
			{
				isSmallStart = true;
				key = _getch();
				if (key == 'b' || key == 'B') {
					isBigMove = true;
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
				smallShip.move(smallShip.getType());
				Sleep(100);
				playingBoard.timeDown();
				printTime(TIME_X, TIME_Y);
			}
		}
	} while (key != ESC);
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

	gameMetadata();

	smallShip = SpaceShip(1, 2, '@', Color::BLUE);
	smallShip.setType(1);
	smallShip.setMat(smallShip.getType());
	smallShip.setArrowKeys("wxad");

	smallShip.initDraw(smallShip.getType());
	bigShip.initDraw(bigShip.getType());

}

void Game::pause() {
	char ch;
	cout << "Game paused, press ESC again to continue or 9 to Exit" << endl;
	do {
		ch = _getch();
	} while (ch != ESC && ch != PAUSE_EXIT);
	if (ch == ESC) {
		run();
	}
	else if (ch == PAUSE_EXIT) {
		userSelection = EXIT;
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
void Game::printTimeText(int x, int y)
{
	setTextColor(Color::WHITE);
	gotoxy(x, y);
	cout << "Time Remains: ";
}


void Game::printLives(int x, int y)
{
	setTextColor(Color::RED);
	gotoxy(x, y);
	for (int i = 0;i < 3;i++)
	{
		cout << ' ';
	}
	gotoxy(x, y);
	for (int i = 0;i < 3;i++)
		cout << "<3";
}
void Game::printLivesText(int x, int y)
{
	setTextColor(Color::WHITE);
	gotoxy(x, y);
	cout << "Lives Remains: ";
}

void Game::gameMetadata()
{
	printLivesText(16, 30);
	printLives(LIVES_X, LIVES_Y);
	printTimeText(16, 29);
	printTime(TIME_X, TIME_Y);
}

//Delete heart in case of dead
void Game::deadHandler()
{
	int heartIndexToDelete = LIVES_X + ((lives - 1) * 2);
	gotoxy(heartIndexToDelete, LIVES_Y);
	cout << "  ";

}

bool Game::timeoutHandler()
{
	return playingBoard.getTimeRemains() > 0;
}
