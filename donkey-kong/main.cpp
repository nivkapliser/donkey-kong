#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
    TODO:
	- finish BarrelManager class - V
	- add Point class - 
	- add Menu class? - in proccess (change name to menuGraphics)
	- if barrel hit ground he should not explode -
	- use getters and setters? -
	- make sure all functions documented, const if needed, etc. -
	- add nicer menu look -
	- Add colors -
*/

int main()
{
	ShowConsoleCursor(false);
	Game game;
	game.run();
	return 0;
}

