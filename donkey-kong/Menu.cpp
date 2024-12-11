#include "Menu.h"

void Menu::displayOpenScreen() {
	system("cls");
	for (int i = 0; i < 23; i++) {
		std::cout << originalBoard[i] << '\n';
	}
	Sleep(2000);
	system("cls");
}

// need to create
void Menu::displayGameOver() {
	system("cls");
	std::cout << "Game Over!\n";
	std::cout << "Press any key to return to menu...\n";
	_getch();
}

// need to create
void Menu::displayGameWon() {
	system("cls");
	std::cout << "Game Over!\n";
	std::cout << "Press any key to return to menu...\n";
	_getch();
}