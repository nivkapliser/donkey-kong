#include "Game.h"
#include "GameFromKeyboard.h"
#include "GameFromFile.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

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

