#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
    TODO:
	- add Point class - ?
	- use getters and setters? -
	- make sure all functions documented, const if needed, etc. -
	- moving the barrel manager ctor to the cpp file - how to?
	- Initialize currentBoard in the Board ctor - ???
	- add a goodbye graphics
*/

int main()
{
	ShowConsoleCursor(false);
	Game game;
	game.run();
	return 0;
}

