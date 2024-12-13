#include "MenuGraphics.h"

// This function prints the graphics to the console.
void MenuGraphics::printGraphics(const char* graphics[]) const {
	system("cls");
	for (int i = 0; i < GRAPHICS_HIGHT; i++) { 
		std::cout << graphics[i] << '\n';
	}
}

// This function displays the game menu.
void MenuGraphics::displayMenu() {
	printGraphics(menu);
}

// This function displays the open screen.
void MenuGraphics::displayOpenScreen() {
	printGraphics(openScreen);
	Sleep(2000);
	system("cls");
}

// This function displays the instructions screen.
void MenuGraphics::displayInstructions()  {
	printGraphics(instructions);
	_getch();
}

// This function displays the game over screen.
void MenuGraphics::displayGameOver() {
	printGraphics(gameOverScreen);
	std::cout << "Press any key to return to menu...\n";
	_getch();
}

// This function displays the game won screen.
void MenuGraphics::displayGameWon() {
	printGraphics(gameWonScreen);
	std::cout << "Press any key to return to menu...\n";
	_getch();
}

// This function displays the stop screen.
void MenuGraphics::displayStopScreen() {
	printGraphics(stopScreen);
}

void MenuGraphics::displayGoodBye() {
	printGraphics(goodBye);
	Sleep(2000);
	system("cls");
}