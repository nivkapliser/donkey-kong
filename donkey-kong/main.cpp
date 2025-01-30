#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

/*
TODO:
1. READ FROM MAIN ARGUMENTS
2. NEED TO FINISH SPACIAL GHOST - NIV  ---------V
3. GHOSTED - OMRI   --------V
4. SILENT - NIV   ----------V
5. HANDLE COLORS - OMRI   --------V
6. CHECK IF FUNCTIONS NEED TO BE CONST
7. HANDLE TYPE_ID - OMRI  --------V
8. CHECK BUGS
*/

int main(int argc, char** argv)
{
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
	
	if (isLoad) {
		GameFromFile gameFromFile(isSilent);
		gameFromFile.run();
	}
	else {
		GameFromKeyboard gameFromKeyboard(isSave);
		gameFromKeyboard.run();
	}
	return 0;
}

