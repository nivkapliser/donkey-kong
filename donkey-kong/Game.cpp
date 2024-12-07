#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

// Initializes the game by resetting the board and setting up mario and barrels
void Game::initGame() {
	board.reset();
	mario.setBoard(board);
	for (int i = 0; i <= MAX_BARRELS - 1; i++)
	{
		barrels[i].setBoard(board);
	}
}

// Resets the stage entities, including the board, mario, and barrels
void Game::resetStage() {
	system("cls");
	board.reset();
	board.print();
	mario.resetMarioPosition();
	mario.setBoard(board);

	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		barrels[i] = Barrel();
		barrels[i].setBoard(board);
	}
}

// Displays the main menu and handles user input for menu selection
void Game::displayMenu() {
	char choice;
	system("cls");
	std::cout << "Donkey Kong\n";
	std::cout << "1. Start New Game\n";
	// add colors?
	std::cout << "8. Instructions\n";
	std::cout << "9. Exit\n";

	while (true) {
		std::cout << "Enter Choice:\n";
		std::cin >> choice;
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

// Displays the game instructions
void Game::displayInstructions() const {
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

// Main game loop to handle different game states
void Game::run() {

	while (true) {
		switch (getGameState()) {
		case MENU:
			displayMenu();
			break;
		case RUNNING:
			resetStage();
			runGame();
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

// Runs the game logic, including handling user input and moving entities
void Game::runGame() {
	int sleepCount = 0;
	int activatedBarrel = 1;
	static int i = 0;

	// moving loop for mario and barrels
	while (true) {
		
		mario.draw();
		drawBarrels();

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

		// barrel activation loop
		if (sleepCount == BARRELS_PACE) // need a separate function for this?
		{
			if(barrels[activatedBarrel].checkActivationStatus() == false)
			{
				barrels[activatedBarrel].barrelActivation();
				activatedBarrel++;
			}
			if (activatedBarrel == MAX_BARRELS)
				activatedBarrel = 0;
			sleepCount = 0;

		}
		sleepCount += 50;

		if (mario.metPauline()) {
			currentState = GAME_WON;
		}

		if (currentState == GAME_OVER) {
			break;
		}
		if (currentState == GAME_WON) {
			break;
		}

	}
}

// Pauses the game and waits for user input to resume or return to menu
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


// no need - can delete:
// ------------------------------------------------
/*
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
	case GAME_OVER:
		// Handle game over
		break;
	}

}
*/

// Displays the game over screen and waits for user input to return to menu
void Game::displayGameOver() { // add nicer graphic
	system("cls");
	std::cout << "GAME OVER!\n";
	std::cout << "Press any key to return to menu...\n";
	_getch();
	currentState = MENU;
}

// Displays the game won screen and waits for user input to return to menu
void Game::displayGameWon() { // add nicer graphic
	system("cls");
	std::cout << "Congratulations! You rescued Pauline!\n";
	std::cout << "Press any key to return to menu...\n";
	_getch();
	currentState = MENU;
}

// shoud be in barrel class?
void Game::drawBarrels()
{
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true)
		{
			barrels[i].draw();
			barrels[i].floorDirSync();
			if (barrels[i].barrelFallManager() == true)
				barrels[i].explode();

			if (barrels[i].checkEncounters(mario))
				if (mario.getLives() == 1) {
					currentState = GAME_OVER;
					mario.downLives();
				}
				else {
					Sleep(250);
					resetStage();
					mario.downLives();
				}	
		}
	}
}


// should be in barrel class?
void Game::moveBarrels()
{
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true)
		{

			if (barrels[i].checkEncounters(mario))
				if (mario.getLives() == 1) {
					currentState = GAME_OVER;
					mario.downLives();
				}
				else {
					Sleep(250);
					resetStage();
					mario.downLives();
				}
				//resetStage();
			barrels[i].erase();
			barrels[i].move();
		}

	}
}
