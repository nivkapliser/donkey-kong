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
				currentState = GameState::RUNNING;
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
				currentState = GameState::FINISH;
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
		case GameState::MENU: // the default game state
			showMenu();
			break;
		case GameState::RUNNING:  // to start the game movement loop
			initGame();
			runGame();
			break;
		case GameState::RESUME: // to resume the game after pausing
			board.print();
			mario.drawLife();
			currentState = GameState::RUNNING;
			runGame();
			break;
		case GameState::PAUSED: // to pause the game
			pauseGame();
			break;
		case GameState::GAME_OVER:	// to display game over screen and return to menu
			menuGraphics.displayGameOver();
			currentState = GameState::MENU;
			break;
		case GameState::GAME_WON: // to display game won screen and return to menu
			menuGraphics.displayGameWon();
			currentState = GameState::MENU;
			break;
		case GameState::FINISH: // to exit the game loop
			run = false;
			break;
		default:
			currentState = GameState::MENU;
			break;
		}

	}
	Sleep(50);
	menuGraphics.displayGoodBye();
}

// Runs the game logic, including handling user input and moving entities
void Game::runGame() {

	// moving loop for mario and barrels
	while (currentState == GameState::RUNNING) {

		mario.draw();
		barrelsManager.drawBarrels(mario); // draw all active barrels
		ghostsManager.drawGhosts(mario);
		hammer.draw();

		// check for user input
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) {
				currentState = GameState::PAUSED;
				break;
			}
			mario.keyPressed(key);
		}
		Sleep(50); // for better visual effect

		// erase and move mario and barrels
		mario.erase();
		mario.move();
		hammer.erase();
		barrelsManager.moveBarrels(mario);
		ghostsManager.moveGhosts(mario);


		barrelsManager.barrelsActivation();

		// if mario encounters a barrel, reset the stage or game over
		checkEncounters(barrelsManager, mario);
		checkEncounters(ghostsManager, mario);
		checkHammer(mario, hammer);

		// check if mario has fallen 5 lines and reset the stage
		if (mario.fellTooFar() && mario.isOnFloor())
			explodeMarioAndResetStage(mario);

		// if mario meets Pauline, game won
		marioMetPauline(mario);

		if (currentState == GameState::GAME_OVER) {
			break;
		}
	}
}

// Pauses the game and waits for user input to resume or return to menu
void Game::pauseGame() {

	menuGraphics.displayStopScreen();
	while (currentState == GameState::PAUSED) {
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) {
				currentState = GameState::RESUME;
			}
			else {
				currentState = GameState::MENU;
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
		currentState = GameState::GAME_OVER;
	}
}

// function to check for encounters of mario and barrels
void Game::checkEncounters(BarrelManager& bm, Mario& mario) {
	if (bm.getEncounters()) {
		//mario.explode();
		mario.downLives();
		resetStage();
		if (mario.getLives() == 0) {
			currentState = GameState::GAME_OVER;
			bm.setEncounters(false);
		}
		bm.setEncounters(false);
	}
}
void Game::checkEncounters(GhostManager& gm, Mario& mario) {
	if (gm.getEncounters()) {
		mario.ghosted();
		mario.downLives();
		resetStage();
		if (mario.getLives() == 0) {
			currentState = GameState::GAME_OVER;
			gm.setEncounters(false);
		}
		gm.setEncounters(false);
	}
}

void Game::checkHammer(Mario& mario, Hammer& hammer) {
	mario.checkIfMetHammer(&hammer);
}

//void Game::updateLegend() {
//	if (hammer.isCollected()) {
//		board.updateLegend("Hammer: Collected");
//	}
//	else {
//		board.updateLegend("Hammer: Not Collected");
//	}
//	printLegend()
//	
//
//}

//void Game::getUserInput() {
//	char key = _getch();
//	if (key == ESC) {
//		currentState = PAUSED;
//	}
//	mario.keyPressed(key);