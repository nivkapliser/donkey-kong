#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
    TODO:
	- use getters and setters? 
	- moving the barrel manager ctor to the cpp file - how to?
	- handle colors for the board
*/

int main()
{
	ShowConsoleCursor(false);
	Game game;
	game.run();
	return 0;
}

