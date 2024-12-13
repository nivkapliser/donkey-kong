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
	if (menuGraphics.getAddColor()) {
		color(LIGHT_RED);
	}
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
	if (menuGraphics.getAddColor()) {
		color(LIGHT_CYAN);
	}
	menuGraphics.displayMenu();	

	while (true) {
		std::cout << "Enter Your Choice:\n";
		std::cin >> choice;
		if (choice == '1') {
			setGameState(RUNNING);
			break;
		}
		else if (choice == '2') {
			menuGraphics.setAddColor(false);
			color(WHITE);
			menuGraphics.displayMenu();
		}
		else if (choice == '8') {
			if (menuGraphics.getAddColor()) {
				color(LIGHT_MAGENTA);
			}
			menuGraphics.displayInstructions();	
			break;
		}
		else if (choice == '9') {
			setGameState(FINISH);
			return;
		}
		else {
			std::cout << "Invalid Choice. Please try again.\n";
		}
	}
	system("cls");

}

// Main game loop to handle different game states
void Game::run() {
	bool run = true;
	if (menuGraphics.getAddColor()) {
		color(LIGHT_MAGENTA);
	}
	menuGraphics.displayOpenScreen();
	while (run) {
		switch (getGameState()) {
		case MENU: // the default game state
			displayMenu();
			break;
		case RUNNING:  // to start the game movement loop
			initGame();	
			runGame();
			break;
		case RESUME: // to resume the game after pausing
			board.print();
			mario.drawLife();
			runGame();
			break;
		case PAUSED: // to pause the game
			pauseGame();
			break;
		case GAME_OVER:	// to display game over screen and return to menu
			if (menuGraphics.getAddColor()) {
				color(LIGHT_RED);
			}
			menuGraphics.displayGameOver();
			setGameState(MENU);
			break;
		case GAME_WON: // to display game won screen and return to menu
			if (menuGraphics.getAddColor()) {
				color(LIGHT_GREEN);
			}
			menuGraphics.displayGameWon();
			setGameState(MENU);
			break;
		case FINISH: // to exit the game loop
			run = false;
			break;
		default: 
			setGameState(MENU);
			break;
		}
		
	}
	Sleep(50);
	std::cout << "Goodbye!\n"; // create graphics for this
}

// Runs the game logic, including handling user input and moving entities
void Game::runGame() {

	// moving loop for mario and barrels
	while (true) {
		if (menuGraphics.getAddColor()) {
			color(LIGHT_GREEN);
		}
		mario.draw();

		// check if mario has fallen 5 lines and reset the stage
		if (mario.fellTooFar() && mario.isOnFloor()) {
			Sleep(500); // for better visual effect
			resetStage();
			mario.downLives();
			if (mario.getLives() == 0) {
				currentState = GAME_OVER;
				break;
			}
		}

		if (menuGraphics.getAddColor()) { // for colors
			color(BROWN);
		}
		barrelsManager.drawBarrels(mario); // draw all active barrels

		if (menuGraphics.getAddColor()) { // for colors
			color(LIGHT_RED);
		}

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
		barrelsManager.barrelsActivation();
		
		// if mario encounters a barrel, reset the stage or game over
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

		// if mario meets Pauline, game won
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
	if (menuGraphics.getAddColor()) {
		color(LIGHT_CYAN);
	}
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
	if (menuGraphics.getAddColor()) {
		color(LIGHT_RED);
	}
}



