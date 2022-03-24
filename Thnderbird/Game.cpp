

#include "Game.h"

using namespace std;

void Game::start() {

	printMenu();
	makeSelection();
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
	do {
		if (_kbhit())
		{
			key = _getch();
			if ((dir = smallShip.getDirection(key)) != -1)
				smallShip.setDirection(dir);
			else if ((dir = smallShip.getDirection(key)) != -1)
				smallShip.setDirection(dir);	
		}
		smallShip.move(smallShip.getType());
		Sleep(1000);
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
	char bigKeys[4] = { 'W','S', 'A', 'D' };
	bigShip = SpaceShip(2, 2, '#', Color::GREEN);
	bigShip.setType(2);
	bigShip.setMat(bigShip.getType());
	bigShip.setArrowKeys(bigKeys);

	//char smallKeys[4] = { 'U','J', 'H', 'K' };
	smallShip = SpaceShip(1, 2, '@', Color::BLUE);
	smallShip.setType(1);
	smallShip.setMat(smallShip.getType());
	smallShip.setArrowKeys("ujhk");

	
	smallShip.move(smallShip.getType());
	
}

void Game::pause() {
	char ch;
	cout << "Game paused, press ESC again to continue or 9 to Exit" << endl;
	do {
		ch = _getch();
	} while (ch != ESC && ch != PAUSE_EXIT);
	if (ch == ESC){
		run();
	}
	else if (ch == PAUSE_EXIT) {
		userSelection = EXIT;
	}
}


