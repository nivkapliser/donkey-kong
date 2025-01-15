#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

/*
	TODO
	4. change Enemy ctor to have no default values - check if can remove - Niv
	5. create a manager class for all entities - Niv
	8. pad with spaces if board too small - Niv
	9. if mario wins, move to next board - Omri -------------------- V
	10. show hammer in legend - Niv -------------------- V
	11. polymorphism for entities - Niv
	13. mario hits in the moving dir - Niv ---------------- V
	15. fix barrels in screen 2. wall and floor (gravitation) - Omri ---------------- V
	16. check for bugs - Omri
	17. check if missing enteties in board file - Niv --------------- V
	18. make enum class - Niv
	19. bug ! - when we input a letter (instead of int) in the board selection the screen blinks and the game not works.
	20. add kbhit loop - Niv
*/


// Initializes the game by resetting the board and setting up mario and barrels
void Game::initGame() {
	mario.resetLives();
	mario.resetScore();
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
	mario.drawScore();
	mario.resetFallCounter();
	hammer.setCollected(false);
	hammer.resetPosition();
	hammer.setBoard(board);
	barrelsManager.reset(board);
	ghostsManager.reset(board);
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
				if (showAndLoadBoards()) {
					currentState = GameState::RUNNING;
					run = false;
				}
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
		else { // need to fix after choosing a board
			system("cls"); // for printing in the screen size
			menuGraphics.displayMenu();
			std::cout << "Invalid Choice. Please try again.\n";
		}
	}
	system("cls");

}

bool Game::showAndLoadBoards() {
	system("cls");
	namespace fs = std::filesystem;
	boardFiles.clear();
	//std::vector<std::string> boardFiles;
	std::string input; // to clear the buffer

	// Scan directory for board files - taken from chatGpt
	for (const auto& entry : fs::directory_iterator(".")) {
		if (entry.path().string().find("dkong_") != std::string::npos &&
			entry.path().string().find(".screen") != std::string::npos) {
			boardFiles.push_back(entry.path().string());
		}
	}

	if (boardFiles.empty()) {
		std::cout << "No board files found. Exiting game.\n";
		return false; // should be State change
	}

	std::cout << "Select a board to load:\n";
	for (size_t i = 0; i < boardFiles.size(); ++i) {
		std::cout << i + 1 << ". " << boardFiles[i] << "\n";
	}

	std::cin >> currentBoardIndex;
	while (!(currentBoardIndex > 0 && currentBoardIndex <= boardFiles.size())) {
		system("cls");
		std::cout << "Select a board to load:\n";
		for (size_t i = 0; i < boardFiles.size(); ++i) {
			std::cout << i + 1 << ". " << boardFiles[i] << "\n";
		}
		std::cout << "Invalid choice. Try again.\n";
		std::cin >> currentBoardIndex;
	}
	if (board.readBoard(boardFiles[currentBoardIndex - 1], mario, hammer) != 1) {
		std::cout << "Error while reading board file. Exiting game.\n";
		Sleep(3000); // so user can see
		return false;
	}
	std::getline(std::cin, input);
	return true;
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
			checkNextStage();
			break;
		case GameState::NEXT_STAGE:
			resetStage();
			runGame();
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
	while (currentState == GameState::RUNNING || currentState == GameState::NEXT_STAGE) {

		mario.draw();
		barrelsManager.draw(mario); // draw all active barrels
		ghostsManager.draw(mario);
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

		checkHammer(mario, hammer); // works better
		if (mario.getSmash()) {
			barrelsManager.smashBarrels(mario);
			ghostsManager.smashGhosts(mario);

			mario.smashOnce();
		}

		barrelsManager.move(mario);
		ghostsManager.move(mario);


		barrelsManager.barrelsActivation();
		
		
		// if mario encounters a barrel, reset the stage or game over
		checkEncounters(barrelsManager, mario);
		checkEncounters(ghostsManager, mario);
		
		if (!ghostsManager.getEncounters() && !barrelsManager.getEncounters())
			mario.drawScore();

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
	mario.checkIfMetHammer();
	if (hammer.isCollected()) {
		gotoxy(board.getLegendX() + 8, board.getLegendY() + 1);
		std::cout << "p";
	}
	else {
		gotoxy(board.getLegendX() + 8, board.getLegendY() + 1);
		std::cout << " ";
	}
}

void Game::smashBarrel(BarrelManager& bm, Mario& mario) {
	if (mario.getSmash()) {
		bm.smashBarrels(mario);	
		mario.smashEnemies();
	}
}

void Game::smashGhost(GhostManager& gm, Mario& mario) {
	if (mario.getSmash()) {
		gm.smashGhosts(mario);
		mario.smashEnemies();
	}
}

void Game::checkNextStage() {
	if (currentBoardIndex < boardFiles.size()) {
		currentBoardIndex++;
		board.readBoard(boardFiles[currentBoardIndex - 1], mario, hammer);
		currentState = GameState::NEXT_STAGE;
	}
	else
		currentState = GameState::MENU;
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