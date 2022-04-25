#include "Game.h"
using namespace std;


/*
This function is used to select color mode to game.
*/
void Game::selectColorMode() const {
	printColorMenu();
	setColorMode();
	clear_screen();
}

/*
This function is used to start the game by printing menu and make a selection.
*/
void Game::start() {

	printMenu();
	makeSelection();
}


/*
This is setter function of lives data member.
*/
void Game::setLives(int _lives)
{
	lives = _lives;
}

/*
This is getter function of lives data member.
*/
int Game::getLives() const
{
	return lives;
}

/*
This function is used to print color menu.
*/
void Game::printColorMenu() const {
	cout << "Select your color mode:" << endl;
	cout << "(1) Colorful" << endl;
	cout << "(2) Black and White" << endl;
}

/*
This function is used to set color mode by user input.
*/
void Game::setColorMode() const {

	int userInput;
	cin >> userInput;
	switch (userInput)
	{
	case COLORFUL:
		isBlackAndWhite = false;
		break;
	case BLACK_WHITE:
		isBlackAndWhite = true;
		break;
	default:
		cout << "Wrong input, please try again !" << endl << endl;
		selectColorMode();
		break;
	}
}

/*
This function is used to print main menu.
*/
void Game::printMenu() const {

	cout << "Welcome to Thunderbirds !" << endl;
	cout << "Please make a selection:" << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(7) Start a new game with specific screen" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

}

/*
This function is used to receive a selection from user according to menu options.
*/
void Game::makeSelection() {
	int userInput;;
	cin >> userInput;
	userSelection = static_cast<GameStatus>(userInput);
	switch (userSelection)
	{
	case GameStatus::INFO:
		showInfo();
		system("pause");
		clear_screen();
		start();
		break;
	case GameStatus::START_FILE_NAME:
		getFileNameFromUser();
	case GameStatus::START:
		init();
		if (!playingBoard.getIsFileLoadFail()) {
			run();
		}
	case GameStatus::EXIT:
		setTextColor(Color::DARKGREY);
		cout << "Goodbye !";
		break;
	default:
		cout << "Wrong input, please try again !" << endl << endl;
		start();
		break;
	}

}

/*
This function manages the main running of the game by user keyboard typing and according to game
status. Function manages ship movement, ship switch, victory check, lose check and pasue of the game.
*/
void Game::run() {

	char key = 0;
	SpaceShip* bigShip = playingBoard.getBigShip();
	SpaceShip* smallShip = playingBoard.getSmallShip();
	do {
		if (isBigMove && !bigShip->getIsExit()) {
			key = moveShip(isBigStart, isBigOnMoving, *smallShip, *bigShip, BIG_SWITCH_KEY, SMALL_SWITCH_KEY);
			checkVictory(bigShip);
			if (bigShip->getIsExit() && gameStatus != GameStatus::VICTORY) {
				switchShip(isBigOnMoving, *smallShip, *bigShip);
			}
		}
		if (!isBigMove && !smallShip->getIsExit()) { // is small move
			key = moveShip(isSmallStart, isSmallOnMoving, *bigShip, *smallShip, SMALL_SWITCH_KEY, BIG_SWITCH_KEY);
			checkVictory(smallShip);
			if (smallShip->getIsExit() && gameStatus != GameStatus::VICTORY) {
				switchShip(isSmallOnMoving, *bigShip, *smallShip);
			}
		}
	} while (key != (int)GameStatus::ESC && !isLose() && gameStatus != GameStatus::VICTORY);
	pause();
}

/*
This function is generic function for ship movement, handles big or small ship.
Funtion manages movement direction according to keyboard typing from user. In addition, function can
stop ships according to user keyboard typing of same switch key.In parallel function manages blocks
falling in whole board and time handle.
*/
char Game::moveShip(bool& isStart, bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove, char curShipswitchKey, char otherShipSwitchKey) {
	char key = 0;
	int dir;
	if (_kbhit())
	{

		isStart = true;
		key = _getch();
		if (key == tolower(otherShipSwitchKey) || key == toupper(otherShipSwitchKey)) {
			if (shipToSwitch.getIsExit() == false)
			{
				switchShip(isOnMoving, shipToSwitch, shipToMove);
			}
		}
		else if (key == tolower(curShipswitchKey) || key == toupper(curShipswitchKey)) {
			isOnMoving = !isOnMoving;
		}
		else if ((dir = shipToMove.getDirection(key)) != NO_DIRECTION) {
			isOnMoving = true;
			shipToMove.setDirection(dir);
		}
	}

	playingBoard.moveGhosts();
	playingBoard.fallBlocksIfNoFloor();
	Sleep(GAME_SPEED);
	if (isStart && isOnMoving) {
		if (!playingBoard.getBigShip()->getIsDie() && !playingBoard.getSmallShip()->getIsDie())
		{
			shipToMove.move(&playingBoard);
			playingBoard.timeDown();
			printTime(playingBoard.getTimeIndexPlace(), playingBoard.getLegendYIndexPlace());
		}
	}

	return key;
}


/*
This function is used to switch ship.
Function update the active ship icons.
*/
void Game::switchShip(bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove) {
	isBigMove = !isBigMove;
	isOnMoving = true;
	printPlayingShip(playingBoard.getShipIndexPlace(), playingBoard.getLegendYIndexPlace(), shipToSwitch);
	shipToMove.setDirection(NO_DIRECTION);
}

/*
Get a file name from user, in case of invalid filename close the program.
*/
void Game::getFileNameFromUser()
{
	string fileName;
	clear_screen();
	cout << "Please insert a file name:" << endl;
	cin >> fileName;
	playingBoard.setPlayingFileName(fileName);
	numOfScreens = 1;
}

/*
Print the playing ship in the given place.
*/
void Game::printPlayingShip(const int x, const int y, const SpaceShip& ship) const
{
	gotoxy(x, y);
	switch (ship.getType())
	{
	case ShipSize::SMALL:
		setTextColor(Color::BLUE);
		cout << "Small";
		break;
	default:
		setTextColor(Color::GREEN);
		cout << "Big  ";
		break;
	}
}

/*
Print the name of the playing board in the given place.
*/
void Game::printPlayingBoardName(const int x, const int y, string fileName) const
{
	gotoxy(x, y);
	setTextColor(Color::LIGHTRED);
	cout << fileName;
}

/*
This function is used to show game instructions and keys.
*/
void Game::showInfo() const {
	setTextColor(Color::YELLOW);
	cout << endl;
	cout << "Instructions: " << endl;
	setTextColor(Color::WHITE);
	cout << "Two 'ships' are trapped inside an ancient Egyptian tomb." << endl << "A big one and a small one." << endl << "The big ship can move or carry blocks of total size 6." << endl << "The small ship can move or carry blocks of total size 2." << endl << "You should make them reaching the exit point in time." << endl << endl;
	setTextColor(Color::YELLOW);
	cout << "Arrow Keys: " << endl;
	setTextColor(Color::WHITE);
	cout << "LEFT:  a or A " << endl;
	cout << "RIGHT: d or D " << endl;
	cout << "UP:    w or W " << endl;
	cout << "DOWN:  x or X " << endl << endl;
	setTextColor(Color::YELLOW);
	cout << "Switch keys:" << endl;
	cout << "(If we were with the this ship already, just STOP the movement of this ship)" << endl;
	setTextColor(Color::WHITE);
	cout << "Switched to the Big Ship:   b or B " << endl;
	cout << "Switched to the Small Ship: s or S " << endl << endl;
}


/*
This function is used to initialize game board and to draw the board on screen and
game metadata printing.
*/
void Game::init() {
	clear_screen();
	playingBoard.initBoard();

	if (!playingBoard.getIsFileLoadFail()) {
		playingBoard.draw();

		gameLegend(*(playingBoard.getBigShip()));
		hideCursor();
	}
}

/*
This function is used to handle pause situation.
Function checks the game status - die situation, victory situation or pause situation
according to user request. Function prints on screen messages according to relevant situation.
Function calls to helper fucntion pauseCheck() which continue the games according to situation.
*/
void Game::pause() {
	char ch = -1;
	int logY = LOG_Y;
	gotoxy(LOG_X, logY);
	if (gameStatus == GameStatus::DIE)
	{
		lives--;
		isBigMove = true;
		setTextColor(Color::YELLOW);
		cout << "You died ";
		if (lives == 0)
		{
			cout << "Game Over, Try your luck next time :) ";
			gameStatus = GameStatus::GAMEOVER;
		}
		else {
			playingBoard.deleteExistDataFromBoard();
			cout << "You have " << lives << " more lives! ";
			Sleep(TIME_TO_PAUSE);

		}
	}
	else if (gameStatus == GameStatus::VICTORY && numOfWins < numOfScreens) {
		gameStatus = GameStatus::NEXT_LEVEL;
		playingBoard.setCurrFileSuffix(playingBoard.getCurrFileSuffix() + 1);
		playingBoard.setPlayingFileName("");
		playingBoard.updatePlayingBoardName();
		printPlayingBoardName(playingBoard.getBoardNameIndexPlace(), 1, playingBoard.getPlayingFileName());
	}
	else if (gameStatus == GameStatus::VICTORY) {
		setTextColor(Color::YELLOW);
		cout << "You won !";
		gotoxy(LOG_X, ++logY);
	}

	else
	{
		setTextColor(Color::LIGHTBLUE);
		cout << "Game paused ";
	}
	pauseCheck(logY);
}

/*
This function is used to handle game accroding to game status in pasue situation.
According to game status, function finished the game in case of game over or in case of victory.
In other case, of die situation or by pause from user request-  waiting for user selection to continue
the game or to exit. Using init() function in case of die in order to reset the board and using
run() function to continue the game.
*/
void Game::pauseCheck(int logY)
{
	char ch = -1;
	switch (gameStatus)
	{
	case GameStatus::GAMEOVER:
	{
		gameStatus = GameStatus::PAUSE_EXIT;
		break;
	}
	case GameStatus::VICTORY:
		gameStatus = GameStatus::PAUSE_EXIT;
		break;
	case GameStatus::NEXT_LEVEL:
		playingBoard.deleteExistDataFromBoard();
		init();
		gameStatus = GameStatus::RUNNING;
		isBigMove = true;
		isBigOnMoving = false;
		isSmallOnMoving = false;
		run();
		break;
	default:
	{
		cout << "press ESC to continue or 9 to Exit ";
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
			isBigOnMoving = false;
			isSmallOnMoving = false;
			run();

		}
		else if (ch == (int)GameStatus::PAUSE_EXIT) {
			setTextColor(Color::DARKGREY);
			userSelection = GameStatus::EXIT;
		}
	}
	}
}

/*
This function is used to print time.
*/
void Game::printTime(const int x, const int y) const
{
	setTextColor(Color::MAGENTA);
	gotoxy(x, y);
	for (int i = 0; i < TIME_LEN; i++)
	{
		cout << ' ';
	}
	gotoxy(x, y);
	cout << playingBoard.getTimeRemains();
}

/*
This function is used to print text description.
*/
void Game::printTextDescription(const int x, const int y, const std::string text) const
{
	setTextColor(Color::WHITE);
	gotoxy(x, y);
	cout << text;
}

/*
This function is used to print lives.
*/
void Game::printLives(const int x, const int y) const
{
	setTextColor(Color::RED);
	gotoxy(x, y);
	for (int i = 0; i < lives; i++)
	{
		cout << ' ';
	}
	gotoxy(x, y);
	for (int i = 0; i < lives; i++)
		cout << "<3";
}

/*
This function is used to prints all game metadata.
*/
void Game::gameLegend(const SpaceShip& ship)
{
	int x = playingBoard.getLegendXIndexPlace(), y = playingBoard.getLegendYIndexPlace();
	std::string liveTextDescription = "Lives: ";
	std::string timeTextDescription = "Time: ";
	std::string playingShipTextDescription = "Ship: ";
	std::string playingBoardTextDescription = "File: ";

	printTextDescription(x, y, liveTextDescription);
	playingBoard.setLiveIndexPlace(x + (int)liveTextDescription.length());
	x += SPACE_BETWEEN_METADATA;
	printLives(playingBoard.getLiveIndexPlace(), y);
	printTextDescription(x, y, timeTextDescription);
	playingBoard.setTimeIndexPlace(x + (int)timeTextDescription.length());
	x += SPACE_BETWEEN_METADATA;
	printTime(playingBoard.getTimeIndexPlace(), y);
	printTextDescription(x, y, playingShipTextDescription);
	playingBoard.setShipIndexPlace(SHIP_X + (int)playingShipTextDescription.length());
	x += SPACE_BETWEEN_METADATA;
	printPlayingShip(playingBoard.getShipIndexPlace(), y, ship);
	printTextDescription(x, y, playingBoardTextDescription);
	playingBoard.setBoardNameIndexPlace(x + (int)playingShipTextDescription.length());
	printPlayingBoardName(playingBoard.getBoardNameIndexPlace(), y, playingBoard.getPlayingFileName());
}

/*
Create equality spaces blocks in the relevant metadata board places.
*/
void Game::makeEmptyMetadataSpaces(const int startXLog, const int topYLog) const
{
	for (int metadataBlock = 0; metadataBlock < 4; metadataBlock++)
	{
		gotoxy(startXLog + 1 + (metadataBlock * 20), topYLog);
		for (int index = 0; index < METADATA_LOG_SIZE; index++)
		{
			cout << ' ';
		}
	}
}

/*
This function is used to delete heart in case of dead and to update it on screen.
*/
void Game::deadHeartHandler()
{
	int heartIndexToDelete = LIVES_X + ((lives - 1) * 2);
	gotoxy(heartIndexToDelete, playingBoard.getLegendYIndexPlace());
	cout << "  ";
	lives--;
}

/*
This function is used to check lose situation.
Checking time out or is ship is smashed and die.
*/
bool Game::isLose()
{
	if (timeoutHandler()) {
		gameStatus = GameStatus::DIE;
		return true;
	}
	if (isSomeShipDie()) {
		gameStatus = GameStatus::DIE;
		return true;
	}
	return false;
}

/*
This function is used to check if there is ship which die.
*/
bool Game::isSomeShipDie()
{
	return (playingBoard.getBigShip()->getIsDie() == true || playingBoard.getSmallShip()->getIsDie() == true);
}

/*
This function is used to check timeout.
*/
bool Game::timeoutHandler() const
{
	return playingBoard.getTimeRemains() <= 0;
}


/*
This function is used to check victory.
Function checks if current ship is already exit.
In case it already exit, checking both ships if they exit.
*/
void Game::checkVictory(SpaceShip* ship) {

	if (!ship->getIsExit()) {
		ship->setIsExit(playingBoard.checkExit(ship));
	}
	if (playingBoard.getBigShip()->getIsExit() == true && playingBoard.getSmallShip()->getIsExit() == true) {
		numOfWins++;
		gameStatus = GameStatus::VICTORY;
	}
}

/*
Distructor of Game.
*/
Game::~Game() {
}