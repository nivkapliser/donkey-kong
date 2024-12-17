#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
    TODO:
	- use getters and setters? 
	- moving the barrel manager ctor to the cpp file - how to?
	- separate mario move to functions
*/

int main()
{
	ShowConsoleCursor(false);
	Game game;
	game.run();
	return 0;
}

