#include "Game.h"


/*
This is main function of Thunderbirds program.
Function creates Game object. Function performs color mode selection and then starts the game.
*/
void main()
{

	Game game;
	game.selectColorMode();
	game.start();

}