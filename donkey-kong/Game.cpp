#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>



void Game::initGame() {
	board.reset();
	mario.setBoard(board);
	for (int i = 0; i <= MAX_BARRELS - 1; i++)
	{
		barrels[i].setBoard(board);
	}
}

void Game::resetStage() {
	board.reset();
	mario = Mario(); // reset Mario
	//barrel = Barrel(); // reset Barrel
	mario.setBoard(board);
	for (int i = 0; i <= MAX_BARRELS - 1; i++)
	{
		barrels[i].setBoard(board);
	}
	lives--;
}

void Game::displayMenu() {
	char choice;
	system("cls");
	std::cout << "Donkey Kong\n";
	std::cout << "1. Start New Game\n";
	std::cout << "8. Instructions\n";
	std::cout << "9. Exit\n";

	while (true) {
		std::cout << "Enter Choice:\n";
		std::cin >> choice;
		GameState state;
		if (choice == '1') {
			setGameState(RUNNING);// need to init new game (mario start at the beggining)
			break;
		}
		else if (choice == '8') {
			displayInstructions();
			break;
		}
		else if (choice == '9') {
			exit(0); // the correct one?
		}
		else {
			std::cout << "Invalid Choice. Please try again.";
		}
	}
	system("cls");

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
		switch (getGameState()) {
		case MENU:
			displayMenu();
			break;
		case RUNNING:
			system("cls");
			board.reset();
			board.print();
			mario.setBoard(board);
			for (int i = 0; i <= MAX_BARRELS; i++)
			{
				barrels[i].setBoard(board);
			}
			runGame();
			//checkCollisions();
			break;

		case PAUSED:
			pauseGame();
			break;
		case GAME_OVER:
			displayGameOver();
			break;
		case GAME_WON:
			displayGameWon();
			break;
		}
	}
	Sleep(50);
}

void Game::runGame() {
	int sleepCount = 0;
	int activateBarrel = 1;
	static int i = 0;
	while (true) {

		drawBarrels();
		mario.draw();

		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) {
				currentState = PAUSED;
				break;
			}
			mario.keyPressed(key);

			drawBarrels();
		}
		Sleep(50);
		mario.erase();
		mario.move();
		moveBarrels();

		if (sleepCount == BARRELS_PACE)
		{
			if(barrels[activateBarrel].checkActivationStatus() == false)
			{
				barrels[activateBarrel].barrelActivation();
				activateBarrel++;
			}
			if (activateBarrel == MAX_BARRELS)
				activateBarrel = 0;
			sleepCount = 0;

		}
		sleepCount += 50;
	}
}

void Game::pauseGame() {
	system("cls");
	std::cout << "Game Paused. Press 'R' to Resume or 'ESC' to Return to Menu.\n";
	while (currentState == PAUSED) {
		if (_kbhit()) {
			char key = _getch();
			if (key == 'r' || key == 'R') {
				currentState = RUNNING;
			}
			else if (key == ESC) {
				currentState = MENU;
			}
		}
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

void Game::drawBarrels()
{
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true)
		{
			barrels[i].draw();
			barrels[i].floorDirSync();
			if (barrels[i].barrelFallManager() == true)
				barrels[i].exploding();
		}
	}
}
void Game::moveBarrels()
{
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true)
		{
			barrels[i].erase();
			barrels[i].move();
		}

	}
}
