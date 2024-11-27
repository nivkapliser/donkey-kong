#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>


void Game::initGame() {
	board.reset();
	mario.setBoard(board);
	barrel.setBoard(board);
}

void Game::resetStage() {
	board.reset();
	mario = Mario(); // reset Mario
	barrel = Barrel(); // reset Barrel
	mario.setBoard(board);
	barrel.setBoard(board);
	lives--; 
}

void Game::displayMenu() {
	system("cls");
	std::cout << "Donkey Kong\n";
	std::cout << "1. Start New Game\n";
	std::cout << "8. Instructions\n";
	std::cout << "9. Exit\n";
	std::cout << "Enter Choice:\n";
}

void Game::displayInstructions() {
	system("cls");
	std::cout << "Game Controls:\n";
	std::cout << "A/D: Move Left/Right\n";
	std::cout << "W: Jump/Climb Up\n";
	std::cout << "X: Climb Down\n";
	std::cout << "S: Stay in Place\n";
	std::cout << "ESC: Pause Game\n";
	std::cout << "Press any key to return...\n";
	_getch();
}

void Game::run() {
	while (true) {
		switch (currentState) {
		case MENU:
			displayMenu();
			break;
		case RUNNING:
			board.print();
			mario.draw();
			barrel.draw();

			if (_kbhit()) {
				char key = _getch();
				handleKeyPress(key);
			}

			barrel.move();
			mario.move(); // switch order?

			//checkCollisions();
			break;

		case PAUSED:
			//need to add
			break;
		case GAME_OVER:
			displayGameOver();
			break;
		case GAME_WON:
			displayGameWon();
			break;
		}

		Sleep(50);
	}

}

void Game::handleKeyPress(char key) {
	switch (currentState) {
	case MENU:
		// Handle menu selection
		break;
	case RUNNING:
		if (key == ESC) { 
			currentState = PAUSED;
		}
		else {
			mario.keyPressed(key);
		}
		break;
	case PAUSED:
		if (key == ESC) { 
			currentState = RUNNING;
		}
		break;
	}
}

void Game::displayGameOver() { // add nicer graphic
	system("cls");
	std::cout << "GAME OVER!\n";
	std::cout << "Press any key to return to menu...\n";
	_getch();
	currentState = MENU;
}

void Game::displayGameWon() { // add nicer graphic
	system("cls");
	std::cout << "Congratulations! You rescued Pauline!\n";
	std::cout << "Press any key to return to menu...\n";
	_getch();
	currentState = MENU;
}