#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <limits>



// Initializes the game by resetting the board and setting up mario and barrels
void Game::initGame() {
	srand(random_seed);
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
	spacialGhost.setBoard(board); // for debug
}

//// Displays the main menu and handles user input for menu selection
//void Game::showMenu() {
//
//	char choice;
//	bool run = true;
//	std::string input; // to clear the buffer
//
//	menuGraphics.displayMenu();
//
//	while (run) {
//		std::cout << "Enter Your Choice: ";
//		std::getline(std::cin, input);
//
//		if (input.length() == 1) {
//			choice = input[0];
//			switch (choice) {
//			case '1':
//				if (showAndLoadBoards()) {
//					currentState = GameState::RUNNING;
//					run = false;
//				}
//				else
//				{
//					currentState = GameState::FINISH;
//					return;
//				}
//				break;
//			case '2':
//				menuGraphics.disableColors();
//				break;
//			case '8':
//				menuGraphics.displayInstructions();
//				run = false;
//				break;
//			case '9':
//				currentState = GameState::FINISH;
//				return;
//			default:
//				system("cls"); // for priting in the screen size
//				menuGraphics.displayMenu();
//				std::cout << "Invalid Choice. Please try again.\n";
//			}
//		}
//		else { 
//			system("cls"); // for printing in the screen size
//			menuGraphics.displayMenu();
//			std::cout << "Invalid Choice. Please try again.\n";
//		}
//	}
//	system("cls");
//
//}

bool Game::showAndLoadBoards() {
	system("cls");
	namespace fs = std::filesystem;
	boardFiles.clear();
	std::string input; // to clear the buffer

	// scan directory for board files
	for (const auto& entry : fs::directory_iterator(".")) {
		if (entry.path().string().find("dkong_") != std::string::npos &&
			entry.path().string().find(".screen") != std::string::npos) {
			boardFiles.push_back(entry.path().string());
		}
	}

	// if no board files found, return false for game exit
	if (boardFiles.empty()) {
		std::cout << "No board files found. Exiting game.\n";
		return false; 
	}

	// display board files and load the selected board
	std::cout << "Select a board to load:\n";
	for (size_t i = 0; i < boardFiles.size(); ++i) {
		std::cout << i + 1 << ". " << boardFiles[i] << "\n";
	}

	std::cin >> currentBoardIndex;
	while (std::cin.fail() || !(currentBoardIndex > 0 && currentBoardIndex <= boardFiles.size())) {
		std::cin.clear(); // clear the error state
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // ignore the remaining input in the buffer
		system("cls");
		std::cout << "Select a board to load:\n";
		for (size_t i = 0; i < boardFiles.size(); ++i) {
			std::cout << i + 1 << ". " << boardFiles[i] << "\n";
		}
		std::cout << "Invalid choice. Try again.\n";
		std::cin >> currentBoardIndex;
	}

	// check if the board file was read successfully
	if (board.readBoard(boardFiles[currentBoardIndex - 1], mario, hammer) != 1) {
		std::cout << "Error while reading board file. Exiting game.\n";
		Sleep(3000); // so user can see
		return false;
	}

	std::getline(std::cin, input);
	return true;
}


// Main game loop to handle different game states
//void Game::run() {
//	bool run = true;
//
//	menuGraphics.displayOpenScreen();
//	while (run) {
//		switch (getGameState()) {
//		case GameState::MENU:		// the default game state
//			showMenu();
//			break;
//		case GameState::RUNNING:	// to start the game movement loop
//			initGame();
//			runGame();
//			break;
//		case GameState::RESUME:		// to resume the game after pausing
//			board.print();
//			mario.drawLife();
//			currentState = GameState::RUNNING;
//			runGame();
//			break;
//		case GameState::PAUSED:		// to pause the game
//			pauseGame();
//			break;
//		case GameState::GAME_OVER:	// to display game over screen and return to menu
//			menuGraphics.displayGameOver();
//			currentState = GameState::MENU;
//			break;
//		case GameState::GAME_WON:	// to display game won screen and return to menu
//			menuGraphics.displayGameWon();
//			checkNextStage();
//			break;
//		case GameState::NEXT_STAGE:	// moving on to the next stage after winning
//			resetStage();
//			runGame();
//			break;
//		case GameState::FINISH:		// to exit the game loop
//			run = false;
//			break;
//		default:
//			currentState = GameState::MENU; // default state
//			break;
//		}
//	}
//	Sleep(50);
//	menuGraphics.displayGoodBye();
//}

// Runs the game logic, including handling user input and moving entities
//void Game::runGame() {
//
//	// moving loop for mario and barrels
//	while (currentState == GameState::RUNNING || currentState == GameState::NEXT_STAGE) {
//
//		mario.draw();
//		barrelsManager.draw(mario);
//		ghostsManager.draw(mario);
//		hammer.draw();
//		spacialGhost.draw(); // for debug
//
//		// check and get user input
//		if (_kbhit()) {
//			std::vector<char> keyBuffer;
//			for (int i = 0; i < 5 && _kbhit(); ++i) {
//				keyBuffer.push_back(_getch());
//			}
//
//			for (char key : keyBuffer) {
//				if (key == ESC) {
//					currentState = GameState::PAUSED;
//					break;
//				}
//				mario.keyPressed(key);
//			}
//		}
//		Sleep(50); // for better visual effect
//		
//		
//		mario.erase();
//		mario.move();
//		hammer.erase();
//
//		// check if mario has met and used hammer
//		checkHammer(mario, hammer); 
//		if (mario.getSmash()) {
//			marioHit();
//		}
//
//		barrelsManager.move(mario);
//		ghostsManager.move(mario);
//		spacialGhost.erase(); // for debug
//		spacialGhost.move(); // for debug
//
//		// if mario encounters a barrel, reset the stage or game over
//		checkBarrelEncounters(barrelsManager, mario);
//		checkGhostEncounters(ghostsManager, mario);
//
//		barrelsManager.barrelsActivation(); // reseting the barrel activation
//		
//		// draw the score 
//		if (!ghostsManager.getEncounters() && !barrelsManager.getEncounters())
//			mario.drawScore();
//
//		// check if mario has fallen 5 lines and reset the stage
//		if (mario.fellTooFar() && mario.isOnFloor())
//			explodeMarioAndResetStage(mario);
//
//		// if mario meets Pauline, game won
//		marioMetPauline(mario);
//
//		if (currentState == GameState::GAME_OVER) {
//			break;
//		}
//	}
//}

// Pauses the game and waits for user input to resume or return to menu
//void Game::pauseGame() {
//
//	menuGraphics.displayStopScreen();
//	while (currentState == GameState::PAUSED) {
//		if (_kbhit()) {
//			char key = _getch();
//			if (key == ESC) {
//				currentState = GameState::RESUME;
//			}
//			else {
//				currentState = GameState::MENU;
//			}
//		}
//	}
//}

// Function to explode mario and reset the stage
void Game::explodeMarioAndResetStage(Mario& mario) {
	mario.explode();
	resetStage();
	mario.downLives();
	/*if (mario.getLives() == 0) {
		currentState = GameState::GAME_OVER;
	}*/
}

//// Function to check for encounters of mario and barrels
//void Game::checkBarrelEncounters(BarrelManager& bm, Mario& mario) {
//	if (bm.getEncounters()) {
//		mario.downLives();
//		resetStage();
//		/*if (mario.getLives() == 0) {
//			currentState = GameState::GAME_OVER;
//		}
//		bm.setEncounters(false);*/
//	}
//}

// Function to check for encounters of mario and ghosts
//void Game::checkGhostEncounters(GhostManager& gm, Mario& mario) {
//	if (gm.getEncounters()) {
//		mario.ghosted();
//		mario.downLives();
//		resetStage();
//		if (mario.getLives() == 0) {
//			currentState = GameState::GAME_OVER;
//		}
//		gm.setEncounters(false);
//	}
//}

// Function to check if mario has met hammer and update the legend
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

// Function to handle smashing barrels
void Game::smashBarrel(BarrelManager& bm, Mario& mario) {
	if (mario.getSmash()) {
		bm.smashBarrels(mario);	
		mario.smashEnemies();
	}
}

// Function to handle smashing ghosts
void Game::smashGhost(GhostManager& gm, Mario& mario) {
	if (mario.getSmash()) {
		gm.smashGhosts(mario);
		mario.smashEnemies();
	}
}

// Function to represent mario hammer hit
void Game::marioHit() {
	char last_char = board.getChar(mario.getX() + 2 * mario.getDirX(), mario.getY());
	gotoxy(mario.getX() + 2 * mario.getDirX(), mario.getY());
	std::cout << 'p';
	Sleep(12);
	barrelsManager.smashBarrels(mario);
	ghostsManager.smashGhosts(mario);

	gotoxy(mario.getX() + 2 * mario.getDirX(), mario.getY());
	std::cout << last_char;
	mario.smashOnce();
}

// Function to check if there is a next stage and move to it
//void Game::checkNextStage() {
//
//	if (currentBoardIndex < boardFiles.size()) {
//		currentBoardIndex++;
//		board.readBoard(boardFiles[currentBoardIndex - 1], mario, hammer);
//		currentState = GameState::NEXT_STAGE;
//	}
//	else
//		currentState = GameState::MENU;
//}
