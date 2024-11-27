#pragma once

#include "Board.h"
#include "Mario.h"
#include "Barrel.h"

constexpr int ESC = 27; // move to?
enum GameState { MENU, RUNNING, PAUSED, GAME_OVER, GAME_WON };

class Game
{	
	Board board;
	Mario mario;
	Barrel barrel;
	int lives;
	GameState currentState = MENU;

	void initGame();
	void resetStage();
	//void checkCollisions();
	void displayMenu();
	void displayInstructions();
	void displayGameOver();
	void displayGameWon();
	//add colors...?

public:
	Game() {
		initGame();
	}

	void setGameState(GameState state) {
		currentState = state;
	}
	GameState getGameState() {
		return currentState;
	}
	void run();
	void runGame();
	void pauseGame();
	void handleKeyPress(char key);
	// color function?
};

