#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

int main()
{
	bool load = 1;
	ShowConsoleCursor(false);
	if (load)
	{
		GameFromFile gameFromFile;
		gameFromFile.run();
	}
	else
	{
		GameFromKeyboard gameFromKeyboard;
		gameFromKeyboard.run();
	}

	return 0;
}

