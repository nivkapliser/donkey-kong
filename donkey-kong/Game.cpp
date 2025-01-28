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
	//barrelsManager.reset(board);
	//ghostsManager.reset(board);
	enemiesManager.reset(board);
	//spacialGhost.setBoard(board); // for debug
}

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

// Function to explode mario and reset the stage
void Game::explodeMarioAndResetStage(Mario& mario) {
	mario.explode();
	resetStage();
	mario.downLives();
}

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

void Game::smashEnemy(EnemiesManager& em, Mario& mario) {
	if (mario.getSmash()) {
		em.smashEnemies(mario);
		mario.smashEnemies();
	}
}

// Function to represent mario hammer hit
void Game::marioHit() {
	char last_char = board.getChar(mario.getX() + 2 * mario.getDirX(), mario.getY());
	gotoxy(mario.getX() + 2 * mario.getDirX(), mario.getY());
	std::cout << 'p';
	Sleep(12);
	enemiesManager.smashEnemies(mario);

	gotoxy(mario.getX() + 2 * mario.getDirX(), mario.getY());
	std::cout << last_char;
	mario.smashOnce();
}

