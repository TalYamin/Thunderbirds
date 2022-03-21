#include <iostream>

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
	case START:
		run();
		break;
	case INFO:
		showInfo();
		break;
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
	cout << "Game is running !" << endl;
	init();
}

void Game::showInfo() {
	cout << "Instructions are here !" << endl;
}

void Game::init() {
	cout << "Game is initialized !" << endl;
}


