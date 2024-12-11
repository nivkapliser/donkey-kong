#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

// Initializes the game by resetting the board and setting up mario and barrels
void Game::initGame() {
	mario.resetLives();
	resetStage();
}

// Resets the stage entities, including the board, mario, and barrels
void Game::resetStage() {
	system("cls");
	board.reset();
	board.print();
	mario.resetMarioPosition();
	mario.setBoard(board);
	mario.drawLife();

	barrelsManager.resetBarrels(board);
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
			setGameState(FINISH);
			return;
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
	bool run = true;
	menu.displayOpenScreen();
	while (run) {
		switch (getGameState()) {
		case MENU:
			displayMenu();
			break;
		case RUNNING:
			initGame();	
			runGame();
			break;
		case PAUSED:
			pauseGame();
			break;
		case GAME_OVER:
			displayGameOver();
			setGameState(MENU);
			break;
		case GAME_WON:
			displayGameWon();
			setGameState(MENU);
			break;
		case FINISH:
			run = false;
			break;
		default: 
			setGameState(MENU);
			break;
		}
		
	}
	Sleep(50);
	std::cout << "Goodbye!\n";
}

// Runs the game logic, including handling user input and moving entities
void Game::runGame() {
	int sleepCount = 0; // move to barrel manager?
	int activatedBarrel = 1; // move to barrel manager?
	//static int i = 0;
	//mario.drawLife();
	// moving loop for mario and barrels
	while (true) {
		
		mario.draw();
		barrelsManager.drawBarrels(mario);

		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) {
				currentState = PAUSED;
				break;
			}
			mario.keyPressed(key);

			//drawBarrels();  need?
		}
		Sleep(50);
		mario.erase();
		mario.move();

		if (mario.getFallCounter() >= 5 && mario.isOnFloor()) {
			resetStage();
			mario.downLives();
			if (mario.getLives() == 0) {
				currentState = GAME_OVER;
				break;
			}
		}

		barrelsManager.moveBarrels(mario);
		barrelsManager.barrelsActivation();

		if (barrelsManager.getEncounters()) {
			mario.downLives();
			resetStage();
			//mario.downLives();
			if (mario.getLives() == 0) {
				currentState = GAME_OVER;
				barrelsManager.setEncounters(false);
				break;
			}
			barrelsManager.setEncounters(false);
		}
		if (mario.metPauline()) {
			currentState = GAME_WON;
			break;
		}

		if (currentState == GAME_OVER) {
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
/*void Game::drawBarrels()
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
					//mario.eraseLife();
					//mario.drawLife();
				}
				//resetStage();
			barrels[i].erase();
			barrels[i].move();
		}

	}
}

// should be in barrel class?
void Game::barrelsActivation() {
	static int sleepCount = 0;
	static int activatedBarrel = 1;

	if (sleepCount == BARRELS_PACE) // need a separate function for this?
	{
		if (barrels[activatedBarrel].checkActivationStatus() == false)
		{
			barrels[activatedBarrel].barrelActivation();
			activatedBarrel++;
		}
		if (activatedBarrel == MAX_BARRELS)
			activatedBarrel = 0;
		sleepCount = 0;

	}
	sleepCount += 50;
}*/