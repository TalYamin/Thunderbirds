#include "Game.h"
#include "GameMode.h"
#include <string.h>
#include <algorithm>

#define SILENT_ARG "-silent"
#define BLACK_WHITE_ARG "no-color"
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
			game.setGameSpeed((int)GameSpeedMode::LOAD_SPEED);
			if (argc > 2 && string(argv[2]) == SILENT_ARG)
			{
				isSilent = true;
				game.setIsSilent(true);
				game.setGameSpeed((int)GameSpeedMode::SILENCE_SPEED);
			}
			else if (argc > 2 && string(argv[2]) == BLACK_WHITE_ARG) {
				isBlackAndWhite = true;
			}
			game.load();
			if (isSilent)
			{
				game.printSilentTestResult();
			}
			break;
		case GameMode::SAVE:
			game.setIsSaveMode(true);
			game.selectColorMode();
			game.start();
			break;
		default:
			cout << "Invliad option, please insert a valid option" << endl;
			break;


		}

	}
	return 0;

}