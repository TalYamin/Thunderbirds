#include "Game.h"
#include "WonderGhost.h"
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

int Game::extractParamFieldFromFile(string& line, size_t pos)
{
	string token = line.substr(0, pos);
	line.erase(0, pos + 1);
	return stoi(token);
}



void Game::load()
{
	handleFilesOnInit();
	if (isGameFromFile) {
		stepsIn.open(playingBoard.getStepsFileName());
		if (isSilent)
		{
			gameSpeed = (int)GameSpeedMode::SILENCE_SPEED;
			resultIn.open(playingBoard.getResultFileName());
		}
	}
	init();
	run();
}


void Game::setGameSpeed(int _speed)
{
	gameSpeed = _speed;
}

int Game::getGameSpeed() const
{
	return gameSpeed;
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

bool Game::getIsGameFromFile()
{
	return isGameFromFile;
}

void Game::setIsGameFromFile(bool _isGameIsFromFile)
{
	isGameFromFile = _isGameIsFromFile;
}

bool Game::getIsSaveMode()
{
	return isSaveMode;
}

void Game::setIsSaveMode(bool _isSaveMode)
{
	isSaveMode = _isSaveMode;
}

void Game::setIsSilent(bool _s)
{
	isSilent = _s;
}

bool Game::getIsSilentTestPass()
{
	return isSilentTestPass;
}

void Game::setIsSilentTestPass(bool _isTestPass)
{
	isSilentTestPass = _isTestPass;
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
		handleFilesOnInit();
		init();
		if (!playingBoard.getIsFileLoadFail()) {
			if (isSaveMode)
			{
				stepsOut.open(playingBoard.getStepsFileName());
				resultOut.open(playingBoard.getResultFileName());
			}
			run();
		}
	case GameStatus::EXIT:
		if (!isSilent) {
			setTextColor(Color::DARKGREY);
			cout << "Goodbye !";
		}
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
void Game::run(char key) {


	SpaceShip* bigShip = playingBoard.getBigShip();
	SpaceShip* smallShip = playingBoard.getSmallShip();

	do {
		if (isBigMove && !bigShip->getIsExit()) {
			key = moveShip(isBigStart, isBigOnMoving, *smallShip, *bigShip, BIG_SWITCH_KEY, SMALL_SWITCH_KEY, key);
			checkVictory(bigShip);
			if (bigShip->getIsExit() && gameStatus != GameStatus::VICTORY) {
				switchShip(isBigOnMoving, *smallShip, *bigShip);
			}
		}
		if (!isBigMove && !smallShip->getIsExit()) { // is small move
			key = moveShip(isSmallStart, isSmallOnMoving, *bigShip, *smallShip, SMALL_SWITCH_KEY, BIG_SWITCH_KEY, key);
			checkVictory(smallShip);
			if (smallShip->getIsExit() && gameStatus != GameStatus::VICTORY) {
				switchShip(isSmallOnMoving, *bigShip, *smallShip);
			}
		}
	} while (key != (int)GameStatus::ESC && !isLose() && gameStatus != GameStatus::VICTORY);
	pause();

	closeFiles();
}


void Game::updateFiles()
{
	playingBoard.setCurrFileSuffix(playingBoard.getCurrFileSuffix() + 1);
	playingBoard.setPlayingFileName("");
	closeFiles();
	playingBoard.setStepsFileName("");
	playingBoard.setResultFileName("");
	playingBoard.updatePlayingBoardName();
	playingBoard.updateSavingFileName();
	playingBoard.updateResultFileName();
}

char Game::handleKey()
{
	char directionKey = 0;
	if (isGameFromFile) {
		if (stepsIn.is_open() && stepsIn.good()) {
			string line;
			getline(stepsIn, line);
			if (!line.empty())
			{
				if (line[0] == (char)GameStatus::PAUSE_EXIT && line.size() == 1)
				{
					return (char)GameStatus::PAUSE_EXIT;
				}
				directionKey = line.at(0);
				size_t pos = 1;
				line.erase(0, pos + 1);//delimiter len
				while ((pos = line.find(GHOST_DELIMITER_SYMBOL)) != string::npos) {
					inferGhostMovement(line, pos);
				}
				inferGhostMovement(line, pos);

			}
		}
	}
	else {
		directionKey = _getch();
		if (isSaveMode)
		{
			if (stepsOut.is_open() && stepsOut.good()) {
				if ((directionKey != '\0' && gameStatus != GameStatus::PAUSE) || directionKey == (int)GameStatus::ESC || directionKey == (int)GameStatus::PAUSE_EXIT) {
					stepsOut << directionKey;
				}
			}
		}
	}
	return directionKey;
}

void Game::inferGhostMovement(string& line, const size_t& pos)
{

	string token = line.substr(0, pos);
	size_t ghostDelimeterPos = token.find(':');
	if (ghostDelimeterPos != string::npos)
	{
		int ghostId = stoi(token.substr(0, ghostDelimeterPos));
		Ghost* ghost = playingBoard.getGhostById(ghostId);
		WonderGhost* wg = dynamic_cast<WonderGhost*>(ghost);
		int ghostDirection = (token[ghostDelimeterPos + 1] - '0');
		wg->setDirection(ghostDirection);
		line.erase(0, pos + 1);//delimiter len
	}
}


/*
This function is generic function for ship movement, handles big or small ship.
Funtion manages movement direction according to keyboard typing from user. In addition, function can
stop ships according to user keyboard typing of same switch key.In parallel function manages blocks
falling in whole board and time handle.
*/
char Game::moveShip(bool& isStart, bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove, char curShipswitchKey, char otherShipSwitchKey, char prevKey) {
	char key = 0;
	int dir;
	if (_kbhit() || isGameFromFile)
	{
		isStart = true;
		key = handleKey();
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
	else if (!_kbhit() && !isGameFromFile && isSaveMode) {
		handleFileInStaticMode(isOnMoving, shipToMove, prevKey);
	}

	if (isBigStart || isSmallStart) {
		playingBoard.moveGhosts(isGameFromFile, stepsIn, stepsOut);
	}
	playingBoard.fallBlocksIfNoFloor();
	Sleep(gameSpeed);
	if (isStart && isOnMoving) {
		if (!playingBoard.getBigShip()->getIsDie() && !playingBoard.getSmallShip()->getIsDie())
		{
			shipToMove.move(&playingBoard);
		}
	}

	if (isBigStart || isSmallStart) {
		playingBoard.timeDown();
		if (!isSilent) {
			printTime(playingBoard.getTimeIndexPlace(), playingBoard.getLegendYIndexPlace());
		}
	}

	if (key == '\0') {
		return prevKey;
	}
	return key;
}


void Game::handleFileInStaticMode(bool& isOnMoving, SpaceShip& shipToMove, char& prevKey) {

	if (stepsOut.is_open() && stepsOut.good()) {
		if (prevKey != '\0' || gameStatus == GameStatus::RUNNING) {

			if (isOnMoving) {
				if (shipToMove.getDirection(prevKey) == NO_DIRECTION) {
					stepsOut << STAY_KEY;
				}
				else {
					stepsOut << shipToMove.getCurrentDirectionKey();
				}
			}
			else if (prevKey != (int)GameStatus::ESC && prevKey != '\0')
			{
				stepsOut << STAY_KEY;
			}
			else prevKey = STAY_KEY;
		}
	}
}

void Game::closeFiles()
{
	if (stepsIn.is_open())
	{
		stepsIn.trunc;
		stepsIn.clear();
		stepsIn.close();
	}
	if (stepsOut.is_open())
	{
		stepsOut.clear();
		stepsOut.close();
	}
	if (resultIn.is_open())
	{
		resultIn.clear();
		resultIn.close();
	}
	if (resultOut.is_open())
	{
		resultOut.clear();
		resultOut.close();
	}
}




/*
This function is used to switch ship.
Function update the active ship icons.
*/
void Game::switchShip(bool& isOnMoving, SpaceShip& shipToSwitch, SpaceShip& shipToMove) {
	isBigMove = !isBigMove;
	printPlayingShip(playingBoard.getShipIndexPlace(), playingBoard.getLegendYIndexPlace(), shipToSwitch);
	isOnMoving = false;
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
	if (!isGameFromFile)
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

void Game::generateSavingFile(ofstream& out) {

	out.open(playingBoard.getStepsFileName());
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
	playingBoard.initBoard(isGameFromFile, isSilent);

	if (!playingBoard.getIsFileLoadFail()) {

		if (!isSilent) {
			playingBoard.draw();
			gameLegend(*(playingBoard.getBigShip()));
		}

		hideCursor();
	}
}

void Game::handleFilesOnInit()
{
	playingBoard.setIsLoadFromFile(isGameFromFile);
	if (playingBoard.getPlayingFileName().empty()) {
		playingBoard.updatePlayingBoardName();
	}
	if (playingBoard.getStepsFileName().empty()) {
		playingBoard.updateSavingFileName();
	}
	if (playingBoard.getResultFileName().empty()) {
		playingBoard.updateResultFileName();
	}
}

void Game::printSilentTestResult() {
	clear_screen();
	isSilent = false;
	setTextColor(Color::WHITE);
	if (isSilentTestPass) {
		cout << "test pass";
	}
	else {
		cout << "test failed";
	}
}

bool Game::isValidSilentTest(char requiredKey)
{
	if (resultIn.is_open() && resultIn.good()) {
		char key;
		string line;
		getline(resultIn, line);
		if (line.empty()) {
			return false;
		}
		else {
			key = line.at(0);
			if (key != requiredKey) {
				return false;
			}
			if (inferTimeFromResFile(line) != playingBoard.getTimeRemains()) {
				return false;
			}
		}
	}
	return true;

}

long Game::inferTimeFromResFile(string& line)
{
	size_t pos = 1;
	line.erase(0, pos + 1);//delimiter 
	long timeFromFile = stol(line);
	return timeFromFile;
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
		if (resultOut.is_open()) {
			resultOut << DIE_KEY << ":" << playingBoard.getTimeRemains() << endl;
		}
		else if (resultIn.is_open() && resultIn.good() && isSilentTestPass) {
			isSilentTestPass = isValidSilentTest(DIE_KEY);
		}
		lives--;
		isBigMove = true;
		if (!isSilent) {
			setTextColor(Color::YELLOW);
			cout << "You died ";
		}
		if (lives == 0)
		{
			if (!isSilent) {
				cout << "Game Over, Try your luck next time :) ";
			}
			gameStatus = GameStatus::GAMEOVER;
		}
		else {
			if (!isSilent) {
				cout << "You have " << lives << " more lives! ";
			}
			Sleep(TIME_TO_PAUSE);
		}
	}
	else if (gameStatus == GameStatus::VICTORY && numOfWins < numOfScreens) {
		gameStatus = GameStatus::NEXT_LEVEL;
		if (resultOut.is_open() && resultOut.good())
		{
			resultOut << FINISH_KEY << ":" << playingBoard.getTimeRemains();
		}
		else if (resultIn.is_open() && resultIn.good() && isSilentTestPass) {
			isSilentTestPass = isValidSilentTest(FINISH_KEY);
		}
		updateFiles();
		if (isGameFromFile) {
			if (!stepsIn.is_open())
			{
				stepsIn.open(playingBoard.getStepsFileName());
			}
			if (isSilent) {
				resultIn.open(playingBoard.getResultFileName());
			}
		}
		else if (isSaveMode) {
			stepsOut.open(playingBoard.getStepsFileName());
			resultOut.open(playingBoard.getResultFileName());
		}
	}
	else if (gameStatus == GameStatus::VICTORY) {
		if (!isSilent) {
			setTextColor(Color::YELLOW);
			cout << "You won !!! ";
		}
	}

	else
	{
		if (!isSilent) {
			setTextColor(Color::LIGHTBLUE);
			cout << "Game paused ";
		}
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
	string ss;

	char ch = -1;
	switch (gameStatus)
	{
	case GameStatus::GAMEOVER:
	{
		gameStatus = GameStatus::PAUSE_EXIT;
		break;
	}
	case GameStatus::VICTORY:
		if (resultOut.is_open() && resultOut.good())
		{
			resultOut << FINISH_KEY << ":" << playingBoard.getTimeRemains();
		}
		else if (resultIn.is_open() && resultIn.good() && isSilentTestPass) {
			isSilentTestPass = isValidSilentTest(FINISH_KEY);
		}
		gameStatus = GameStatus::PAUSE_EXIT;
		break;
	case GameStatus::NEXT_LEVEL:
		playingBoard.deleteExistDataFromBoard();
		handleFilesOnInit();
		init();
		gameStatus = GameStatus::RUNNING;
		isBigMove = true;
		isBigOnMoving = false;
		isSmallOnMoving = false;
		run(STAY_KEY);
		break;
	default:
	{
		gameStatus = GameStatus::PAUSE;

		if (!isSilent) {
			cout << "press ESC to continue or 9 to Exit ";
		}
		do {

			ch = handleKey();
		} while (ch != (int)GameStatus::ESC && ch != (int)GameStatus::PAUSE_EXIT);
		if (ch == (int)GameStatus::ESC) {
			claer_line(logY);
			setTextColor(Color::WHITE);

			if (isLose())
			{
				handleNewBoardMovement();
				playingBoard.deleteExistDataFromBoard();
				handleFilesOnInit();
				init();
				ch = STAY_KEY;
			}
			gameStatus = GameStatus::RUNNING;
			isBigOnMoving = false;
			isSmallOnMoving = false;
			run(ch);

		}
		else if (ch == (int)GameStatus::PAUSE_EXIT) {
			setTextColor(Color::DARKGREY);
			userSelection = GameStatus::EXIT;
		}
	}
	}
}

void Game::handleNewBoardMovement()
{
	if (stepsOut.is_open() && stepsOut.good()) {
		stepsOut << endl;
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
	playingBoard.setShipIndexPlace(x + (int)playingShipTextDescription.length());
	x += SPACE_BETWEEN_METADATA;
	printPlayingShip(playingBoard.getShipIndexPlace(), y, ship);
	printTextDescription(x, y, playingBoardTextDescription);
	playingBoard.setBoardNameIndexPlace(x + (int)playingShipTextDescription.length());
	printPlayingBoardName(playingBoard.getBoardNameIndexPlace(), y, playingBoard.getPlayingFileName());
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