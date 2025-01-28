#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
TODO:
1. READ FROM MAIN ARGUMENTS
2. NEED TO FINISH SPACIAL GHOST - NIV
3. GHOSTED - OMRI
4. SILENT - NIV
5. HANDLE COLORS - OMRI
6. CHECK IF FUNCTIONS NEED TO BE CONST
7. HANDLE TYPE_ID - OMRI
*/

int main()
{
	bool load = 1;
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

