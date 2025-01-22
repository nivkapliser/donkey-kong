#include "Game.h"
#include "GameFromKeyboard.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

int main()
{
	ShowConsoleCursor(false);
	GameFromKeyboard gameFromKeyboard;
	gameFromKeyboard.run();
	return 0;
}

