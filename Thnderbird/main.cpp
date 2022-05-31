#include "Game.h"
#include "GameMode.h"
#include <string.h>
#include <algorithm>

#define SILENT_ARG "silent"

/*
This is main function of Thunderbirds program.
Function creates Game object. Function performs color mode selection and then starts the game.
*/
int main(int argc, char* argv[])
{
	Game game;
	bool isSilent = false;
	string fileName;

	if (argc == 1)
	{
		game.selectColorMode();
		game.start();
	}
	else
	{
		string args = argv[1];
		std::for_each(args.begin(), args.end(), [](char& c) {
			c = ::tolower(c);
			});
		switch (getMode(args))
		{
		case GameMode::LOAD:

			game.setIsGameFromFile(true);
			game.init();
			if (argc > 2 && argv[3] == SILENT_ARG)
			{
				isSilent = true;
				game.setGameSpeed((int)GameSpeedMode::SILENCE_SPEED);
			}
			game.load(isSilent);
			break;
		case GameMode::SAVE:
			break;
		default:
			cout << "Invliad option, please insert a valid option" << endl;
			break;


		}

	}
	return 0;

}