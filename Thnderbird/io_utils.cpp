#include "io_utils.h"
#include "Color.h"

using namespace std;

bool isBlackAndWhite;

#ifndef WINDOWS
void gotoxy(int x, int y) {}
int _getch(void) { return 0; }
int _kbhit(void) { return 0; }
void Sleep(unsigned long) {}
void setTextColor(Color color) {}
void hideCursor() {}
void clear_screen() {}
void claer_line(int y)
{
}
#else

/*
This function is used to take the cursor to specific x and y coordiantes.
*/
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

/*
This function is used to set color to text.
In case of isBlackAndWhite mode this is disabled.
*/
void setTextColor(Color colorToSet) {
	if (!isBlackAndWhite) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
	}
}

/*
This function is used to hideCursor.
*/
void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

/*
This function is used to clear screen.
*/
void clear_screen()
{
	system("cls");
}

/*
This function is used to clear line.
*/
void claer_line(int y)
{
	int i;
	gotoxy(0, y);
	for (i = 0;i < HORIZONTAL_SIZE;i++)
		cout << " ";
}
#endif


