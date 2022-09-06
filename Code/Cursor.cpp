#include <iostream>
#include <Windows.h>
#include "Cursor.h"

void Speed(int speed)
{
	Sleep(1000 / speed);
}


void MoveXY(int x, int y, int speed)
{
	Speed(speed);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}