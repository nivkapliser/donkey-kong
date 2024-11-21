#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "utils.h"
#include "Mario.h"

using std::cout;
constexpr int ESC = 27;

int main()
{
	Board board;
	Mario mario;
	board.reset();
	board.print();
	mario.setBoard(board);
	while (true) {
		mario.draw();
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) break;
			mario.keyPressed(key);
		}
		Sleep(50);
		mario.erase();
		mario.move();
	}

	return 0;
}

