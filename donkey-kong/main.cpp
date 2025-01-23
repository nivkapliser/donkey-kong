#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

int main()
{
	ShowConsoleCursor(false);
	GameFromKeyboard gameFromKeyboard;
	GameFromFile gameFromFile;
	//gameFromFile.run();
	gameFromKeyboard.run();
	return 0;
}

