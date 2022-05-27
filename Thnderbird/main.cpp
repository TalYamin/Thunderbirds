#include "Game.h"


/*
This is main function of Thunderbirds program.
Function creates Game object. Function performs color mode selection and then starts the game.
*/
int main(int argc,char*argv[])
{
	Game game;
	bool isSilence = false;
	if (argc == 1)
	{
		game.selectColorMode();
		game.start();
	}
	else
	{
		//TODO: make really good switch case
		switch (1)
		{
		case 1:
			game.load(isSilence);
			break;
		default:
			break;
		}
	}
	return 0;
	
}