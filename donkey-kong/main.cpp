#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>


int main()
{
	ShowConsoleCursor(false);
	Game game;
	game.run();
	return 0;
	//Board board;
	//Mario mario;
	//board.reset();
	//board.print();
	//mario.setBoard(board);
	//Barrel barrel;
	//barrel.setBoard(board);
	//while (true) {
	//	barrel.draw();
	//	barrel.floorDirSync();
	//	mario.draw();
	//	if (_kbhit()) {
	//		char key = _getch();
	//		if (key == ESC) break;
	//		mario.keyPressed(key);
	//	}
	//	Sleep(50);
	//	mario.erase();
	//	mario.move();
	//	
	//	barrel.erase();
	//	barrel.move();
	//}

	return 0;
}

