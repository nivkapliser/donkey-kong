#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
TODO:
1. READ FROM MAIN ARGUMENTS
2. MAKE A RESULT CLASS
3. SPLIT showAndLoadBoards FUNCTION
4. SAVE IS NOT A DEFAULT OPTION. NEED TO DECIDE HOW TO SAVE ACCORDINGLY
5. STEPS RECCORDING DOES NOT OVERRIDE THE EXISTING FILES - PROBABLY NEED TO SAVE AFTER EACH STAGE
6. CHECK IF FUNCTIONS NEED TO BE CONST
*/

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
		GameFromKeyboard gameFromKeyboard(true);
		gameFromKeyboard.run();
	}

	return 0;
}

