#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>


int main()
{
	ShowConsoleCursor(false);
	Game game;
	game.run();
	std::cout << "try";
	return 0;
}

