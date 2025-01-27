#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
TODO:
1. READ FROM MAIN ARGUMENTS
4. SAVE IS NOT A DEFAULT OPTION. NEED TO DECIDE HOW TO SAVE ACCORDINGLY
6. CHECK IF FUNCTIONS NEED TO BE CONST
*/

int main()
{
	bool load = 0;
	ShowConsoleCursor(false);
	if (load) {
		GameFromFile gameFromFile;
		gameFromFile.run();
	}
	else {
		GameFromKeyboard gameFromKeyboard(true);
		gameFromKeyboard.run();
	}
	return 0;
}

