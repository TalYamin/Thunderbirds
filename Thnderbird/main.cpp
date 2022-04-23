#include "Game.h"


/*
This is main function of Thunderbirds program.
Function creates Game object. Function performs color mode selection and then starts the game.
*/
int main()
{
	Game game;
	game.selectColorMode();
	game.start();
	return 0;
}