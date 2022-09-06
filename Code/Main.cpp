#include <iostream>

#include "MoveLogic.h"

int main()
{
	int row, col, speed;
	std::cout << "행, 열, 속도를 입력하세요 : ";
	std::cin >> row >> col >> speed;

	Spiral(row, col, speed);
}