#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "MoveLogic.h"

class Move
{
private:
	std::vector<std::vector<int>> map;
	int tx, ty, speed;
	int x, y;
	int sign;
	int num;
	int direction = 0; // 0 오른쪽, 1 아래, 2 왼쪽, 3 위쪽
	int moveCount = 0;
public:
	int count;

	Move(int tx, int ty, int moveSpeed);
	void MoveCursor(char pause);
	void FirstMove(char);
	void Pause(char sp);
	void End(char sp);
	void SubtractXY();
	void SubtractX();
	void SubtractY();
	void MoveCircle(char);

};
void SwitchingConsoleCursor(bool flag);

Move::Move(int sizex, int sizey, int moveSpeed)
{
	tx = sizex;
	ty = sizey;
	speed = moveSpeed;
	map.resize(ty, std::vector<int>(tx, 0));
	x = y = count = 0;
	sign = num = 1;
}

void Move::MoveCursor(char pause)
{
	const int ROOT = 2147483646;
	Pause(pause);
	map[y][x] = ROOT;
	MoveXY(x + 5, y + 5, speed);
	std::cout << "X";
}

void Move::SubtractXY()
{
	moveCount = 0;
	direction++;
	tx--;
	ty--;
}

void Move::SubtractX()
{
	moveCount = 0;
	direction++;
	tx--;
}

void Move::SubtractY()
{
	moveCount = 0;
	direction++;
	ty--;
}

void Move::FirstMove(char pause)
{
	const int ROOT = 2147483646; // ROOT : 지나간 길

	SwitchingConsoleCursor(false);
	system("cls");

	// 최초 오른쪽 이동
	for (int i = 1; i < tx; ++i)
	{
		count++;
		map[y][x] = ROOT;
		MoveCursor(pause);
		std::cout << "X";

		x += sign;
	}
	y++;
	SubtractXY();
}

void Move::MoveCircle(char pause)
{
	const int ROOT = 2147483646;
	if (direction == 0 && moveCount < tx)
	{
		MoveCursor(pause);
		x += sign;
		moveCount++;
		count++;
		if (moveCount == tx)
		{
			x -= 1;
			y += 1;
			SubtractX();
		}
	}
	else if (direction == 1 && moveCount < ty)
	{
		MoveCursor(pause);
		y += sign;
		moveCount++;
		count++;
		if (moveCount == ty)
		{
			sign *= -1;
			y -= 1;
			x -= 1;
			SubtractY();
		}
	}

	else if (direction == 2 && moveCount < tx)
	{
		MoveCursor(pause);
		x += sign;
		moveCount++;
		count++;
		if (moveCount == tx)
		{
			y -= 1;
			x += 1;
			SubtractX();
		}
	}

	else if (direction == 3 && moveCount < ty)
	{
		MoveCursor(pause);
		y += sign;
		moveCount++;
		count++;
		if (moveCount == ty)
		{
			sign *= -1;
			y += 1;
			x += 1;
			SubtractY();
			direction %= 4;
		}
	}
}

void Move::End(char sp)
{
	const int CURSORSPEED = 10;
	bool flag = true;
	while (flag)
	{
		MoveXY(x + 5, y + 5, CURSORSPEED);
		std::cout << " ";
		MoveXY(x + 5, y + 5, CURSORSPEED);
		//std::cout << "X";
		std::cout << "\x1b[ 0 SX";
		if (_kbhit())
		{
			sp = _getch();
			if (sp == 0x20)
			{
				flag = !flag;
			}
		}
	}
}

void Move::Pause(char sp)
{
	if (_kbhit())
	{
		sp = _getch();
		if (sp == 0x20)
		{
			End(sp);
		}
	}

}

void SwitchingConsoleCursor(bool flag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int checkSpeed(int speed) {
	while (speed > 5 || speed < 1) 
	{
		std::cin.ignore();
		std::cout << "속도는 음수 또는 5를 넘을 수 없습니다. 다시 입력해 주세요 : ";
		std::cin >> speed;		
	}

	return speed;
}

void Spiral(int row, int col, int speed)
{
	char pause = 'a';
	speed = checkSpeed(speed);

	Move a(row, col, speed);


	a.FirstMove(pause);
	while (true)
	{
		a.Pause(pause);
		a.MoveCircle(pause);
		if (a.count == (row * col) - 2)
		{
			a.End(pause);
			MoveXY(0, 1000, 5);
			break;
		}
	}
}