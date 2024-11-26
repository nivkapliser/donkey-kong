#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "utils.h"
#include "Mario.h"
#include "Barrel.h"

using std::cout;
constexpr int ESC = 27;

int main()
{
	ShowConsoleCursor(false);
	Board board;
	Mario mario;
	board.reset();
	board.print();
	mario.setBoard(board);
	Barrel barrel;
	barrel.setBoard(board);
	while (true) {
		barrel.draw();
		barrel.floorDirSync();
		mario.draw();
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) break;
			mario.keyPressed(key);
		}
		Sleep(50);
		mario.erase();
		mario.move();
		
		barrel.erase();
		barrel.move();
	}

	return 0;
}

