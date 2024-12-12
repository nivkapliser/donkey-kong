#pragma once

/*
* This class is the main class of the game. It manages the game state, flow, and controls the game loop.
* It also initializes the game and handles user input. 
*/
#include "utils.h"
#include "Board.h"
#include "Mario.h"
#include "BarrelManager.h"
#include "Barrel.h"
#include "MenuGraphics.h"


class Game
{
	static constexpr int ESC = 27; // ASCII value for the escape key
	enum GameState { MENU, RUNNING, PAUSED, RESUME, GAME_OVER, GAME_WON, FINISH }; // To manage game state for better game control
	
	MenuGraphics menuGraphics; 
	Board board;
	Mario mario;
	BarrelManager barrelsManager;

	GameState currentState = MENU;

	
	void resetStage(); 
	void displayMenu();  
	

public:
	Game(): currentState(MENU), barrelsManager(board) {
		mario.setBoard(board);
	}

	void initGame();

	// Function to set the game state
	void setGameState(GameState state) {
		currentState = state;
	}
	
	// Function to get the game state
	GameState getGameState() {
		return currentState;
	}

	void run();
	void runGame();
	void pauseGame();
};

