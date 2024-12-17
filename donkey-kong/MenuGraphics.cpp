#include "MenuGraphics.h"

// This function sets the color of the console.
// based on the instructions code
void MenuGraphics::setColor(int color) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// This function prints the graphics to the console.
void MenuGraphics::printGraphics(const char* graphics[]) const {
	system("cls");
	for (int i = 0; i < GRAPHICS_HIGHT; i++) { 
		std::cout << graphics[i] << '\n';
	}
}

// This function displays the game menu.
void MenuGraphics::displayMenu() {
	if (addColor) {
		setCurrentColor(LIGHT_CYAN);
	}
	printGraphics(menu);
}

// This function displays the open screen.
void MenuGraphics::displayOpenScreen() {
	if (addColor) {
		setCurrentColor(LIGHT_MAGENTA);
	}
	printGraphics(openScreen);
	Sleep(2000);
	system("cls");
}

// This function displays the instructions screen.
void MenuGraphics::displayInstructions()  {
	if (addColor) {
		setCurrentColor(LIGHT_MAGENTA);
	}
	printGraphics(instructions);
	_getch();
}

// This function displays the game over screen.
void MenuGraphics::displayGameOver() {
	if (addColor) {
		setCurrentColor(LIGHT_RED);
	}
	printGraphics(gameOverScreen);
	std::cout << "Press any key to return to menu...\n";
	_getch();
}

// This function displays the game won screen.
void MenuGraphics::displayGameWon() {
	if (addColor) {
		setCurrentColor(LIGHT_GREEN);
	}
	printGraphics(gameWonScreen);
	std::cout << "Press any key to return to menu...\n";
	_getch();
}

// This function displays the stop screen.
void MenuGraphics::displayStopScreen() {
	if (addColor) {
		setCurrentColor(LIGHT_RED);
	}
	printGraphics(stopScreen);
}

// This function displays the good bye screen.
void MenuGraphics::displayGoodBye() {
	if (addColor) {
		setCurrentColor(LIGHT_CYAN);
	}
	printGraphics(goodBye);
	Sleep(2000);
	system("cls");
}

// This function disables the colors in the game.
void MenuGraphics::disableColors() {
	addColor = false;
	setCurrentColor(WHITE);
	displayMenu();
}