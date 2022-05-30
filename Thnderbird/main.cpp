#include "Game.h"
#include "GameMode.h"

/*
This is main function of Thunderbirds program.
Function creates Game object. Function performs color mode selection and then starts the game.
*/
int main(int argc, char* argv[])
{
	Game game;
	bool isSilence = false;
	string fileName;

	if (argc == 1)
	{
		game.selectColorMode();
		game.start();
	}
	else
	{
		if (argv[2] == (char*)GameMode::LOAD)
		{
			//fileName = argv[3];
			game.setIsGameFromFile(true);
			game.init();
			game.load(false);
			//if (argc == 4)//silence mode
			//{
			//}

		}
		else if (argv[2] == (char*)GameMode::SAVE)
		{
		}
		else
		{
			cout << "Invliad option, please insert a valid option" << endl;
		}



		return 0;
	}
}