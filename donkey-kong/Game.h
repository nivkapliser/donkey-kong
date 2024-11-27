#pragma once

#include "Board.h"
#include "Mario.h"
#include "Barrel.h"

constexpr int ESC = 27; // move to?

class Game
{	
	enum GameState { MENU, RUNNING, PAUSED, GAME_OVER, GAME_WON };
	Board board;
	Mario mario;
	Barrel barrel;
	int lives;
	GameState currentState;

	void initGame();
	void resetStage();
	//void checkCollisions();
	void displayMenu();
	void displayInstructions();
	void displayGameOver();
	void displayGameWon();
	//add colors...?

public:
	Game();
	void setGameState();
	void getGameState();
	void run();
	void handleKeyPress(char key);
	// color function?
};

