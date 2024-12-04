#pragma once

#include "Board.h"
#include "Mario.h"
#include "Barrel.h"


class Game
{

	static constexpr int ESC = 27; 
	enum GameState { MENU, RUNNING, PAUSED, GAME_OVER, GAME_WON };
	
	Board board;
	Mario mario;
	Barrel barrels[MAX_BARRELS]; // vector?
	
	int lives;
	GameState currentState = MENU;

	void initGame();
	void resetStage();
	void displayMenu();
	void displayInstructions() const;
	void displayGameOver();
	void displayGameWon();
	//add colors...?

public:
	Game(): lives(3), currentState(MENU) {
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
	
	void drawBarrels();
	void eraseBarrels(); // delete?
	void moveBarrels();
	// color function?
};

