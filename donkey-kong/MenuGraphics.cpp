#include "MenuGraphics.h"

void MenuGraphics::displayMenu() {
	system("cls");
	for (int i = 0; i < 23; i++) { // create a constant for 23
		std::cout << menu[i] << '\n';
	}
}

void MenuGraphics::displayOpenScreen() {
	system("cls");
	for (int i = 0; i < 23; i++) { // create a constant for 23
		std::cout << openScreen[i] << '\n';
	}
	Sleep(2000);
	system("cls");
}

void MenuGraphics::displayInstructions() const {
	system("cls");
	for (int i = 0; i < 22; i++) { // create a constant for 25
		std::cout << instructions[i] << '\n';
	}
	_getch();
}

// need to create
void MenuGraphics::displayGameOver() {
	system("cls");
	for (int i = 0; i < 23; i++) { // create a constant for 23
		std::cout << gameOverScreen[i] << '\n';
	}
	std::cout << "Press any key to return to menu...\n";
	_getch();
}

// need to create
void MenuGraphics::displayGameWon() {
	system("cls");
	for (int i = 0; i < 23; i++) { // create a constant for 23
		std::cout << gameWonScreen[i] << '\n';
	}
	std::cout << "Press any key to return to menu...\n";
	_getch();
}