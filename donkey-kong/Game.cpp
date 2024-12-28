#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>


/*
	TODO:
	1. add update design pattern for better readability and entity management
	2. split the game loop into smaller functions for better readability
	3. add more State design pattern to the entities for better game state management
	4. add Point?
	5. create a manager class for all entities?
*/


// Initializes the game by resetting the board and setting up mario and barrels
void Game::initGame() {
	mario.resetLives();
	mario.resetFallCounter();
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
	ghostsManager.resetGhosts(board);
}

// Displays the main menu and handles user input for menu selection
void Game::showMenu() {
	char choice;
	bool run = true;
	std::string input; // to clear the buffer

	menuGraphics.displayMenu();

	while (run) {
		std::cout << "Enter Your Choice: ";
		std::getline(std::cin, input);

		if (input.length() == 1) {
			choice = input[0];
			switch (choice) {
			case '1':
				currentState = RUNNING;
				run = false;
				break;
			case '2':
				menuGraphics.disableColors();
				break;
			case '8':
				menuGraphics.displayInstructions();
				run = false;
				break;
			case '9':
				currentState = FINISH;
				return;
			default:
				system("cls"); // for priting in the screen size
				menuGraphics.displayMenu();
				std::cout << "Invalid Choice. Please try again.\n";
			}
		}
		else {
			system("cls"); // for printing in the screen size
			menuGraphics.displayMenu();
			std::cout << "Invalid Choice. Please try again.\n";
		}
	}
	system("cls");

}

// Main game loop to handle different game states
void Game::run() {
	bool run = true;

	menuGraphics.displayOpenScreen();
	while (run) {
		switch (getGameState()) {
		case MENU: // the default game state
			showMenu();
			break;
		case RUNNING:  // to start the game movement loop
			initGame();
			runGame();
			break;
		case RESUME: // to resume the game after pausing
			board.print();
			mario.drawLife();
			currentState = RUNNING;
			runGame();
			break;
		case PAUSED: // to pause the game
			pauseGame();
			break;
		case GAME_OVER:	// to display game over screen and return to menu
			menuGraphics.displayGameOver();
			currentState = MENU;
			break;
		case GAME_WON: // to display game won screen and return to menu
			menuGraphics.displayGameWon();
			currentState = MENU;
			break;
		case FINISH: // to exit the game loop
			run = false;
			break;
		default:
			currentState = MENU;
			break;
		}

	}
	Sleep(50);
	menuGraphics.displayGoodBye();
}

// Runs the game logic, including handling user input and moving entities
void Game::runGame() {

	// moving loop for mario and barrels
	while (currentState == RUNNING) {

		mario.draw();
		barrelsManager.drawBarrels(mario); // draw all active barrels
		ghostsManager.drawGhosts(mario);

		// check for user input
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) {
				currentState = PAUSED;
				break;
			}
			mario.keyPressed(key);
		}
		Sleep(50); // for better visual effect

		// erase and move mario and barrels
		mario.erase();
		mario.move();

		barrelsManager.moveBarrels(mario);
		ghostsManager.moveGhosts(mario);


		barrelsManager.barrelsActivation();
		ghostsManager.ghostsActivation();

		// if mario encounters a barrel, reset the stage or game over
		checkEncounters(barrelsManager, mario);

		// check if mario has fallen 5 lines and reset the stage
		if (mario.fellTooFar() && mario.isOnFloor())
			explodeMarioAndResetStage(mario);

		// if mario meets Pauline, game won
		marioMetPauline(mario);

		if (currentState == GAME_OVER) {
			break;
		}
	}
}

// Pauses the game and waits for user input to resume or return to menu
void Game::pauseGame() {

	menuGraphics.displayStopScreen();
	while (currentState == PAUSED) {
		if (_kbhit()) {
			char key = _getch();
			if (key == 'r' || key == 'R') {
				currentState = RESUME;
			}
			else if (key == ESC) {
				currentState = MENU;
			}
		}
	}
}

// Function to explode mario and reset the stage
void Game::explodeMarioAndResetStage(Mario& mario) {
	mario.explode();
	resetStage();
	mario.downLives();
	if (mario.getLives() == 0) {
		currentState = GAME_OVER;
	}
}

// function to check for encounters of mario and barrels
void Game::checkEncounters(BarrelManager& bm, Mario& mario) {
	if (bm.getEncounters()) {
		mario.downLives();
		resetStage();
		if (mario.getLives() == 0) {
			currentState = GAME_OVER;
			bm.setEncounters(false);
		}
		bm.setEncounters(false);
	}
}

//void Game::getUserInput() {
//	char key = _getch();
//	if (key == ESC) {
//		currentState = PAUSED;
//	}
//	mario.keyPressed(key);