#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
TODO:
1. WHEN PAULINE RESCUED, BOARD IS NOT CHANGE TO THE NEXT BOARD (PROBABLY SETTER ISSUE IN FUNCTION checkNextStage)
2. MAKE A RESULT CLASS
3. SPLIT showAndLoadBoards FUNCTION
*/

int main()
{
	bool load = 0;
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

