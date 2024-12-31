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
#include "Ghost.h"
#include "GhostManager.h"

class Game
{
	static constexpr int ESC = 27; // ASCII value for the escape key
	static constexpr char PAULINE = '$';
	enum GameState { MENU, RUNNING, PAUSED, RESUME, GAME_OVER, GAME_WON, FINISH }; // To manage game state for better game control


	MenuGraphics menuGraphics;
	Board board;
	Mario mario;
	BarrelManager barrelsManager;
	GhostManager ghostsManager;


	GameState currentState = MENU;


	void resetStage();
	void showMenu();
	void initGame();
	void runGame();
	void pauseGame();


public:
	Game() : currentState(MENU), ghostsManager(board, &menuGraphics), barrelsManager(board, &menuGraphics), mario(&menuGraphics), board(&menuGraphics) {
		mario.setBoard(board);
	}

	// Function to get the game state
	GameState getGameState() const {
		return currentState;
	}

	// Function to check if mario met Pauline and won the game
	void marioMetPauline(Mario& mario) {
		if (mario.metPauline())
			currentState = GAME_WON;
	}

	void run();
	void explodeMarioAndResetStage(Mario& mario);
	void checkEncounters(BarrelManager& bm, Mario& mario);
	void checkEncounters(GhostManager& gm, Mario& mario);

};