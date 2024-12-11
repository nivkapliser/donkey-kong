#pragma once
#include "Board.h"
#include "Mario.h"
#include "BarrelManager.h"
#include "Barrel.h"
#include "Menu.h"


class Game
{
	
	static constexpr int ESC = 27; 
	static constexpr int MAX_BARRELS = 20;
	static constexpr int BARRELS_PACE = 700;
	enum GameState { MENU, RUNNING, PAUSED, GAME_OVER, GAME_WON, FINISH }; // To manage game state for better game control
	
	Menu menu;
	Board board;
	Mario mario;
	BarrelManager barrelsManager;
	GameState currentState = MENU;

	
	void resetStage();
	void displayMenu();
	void displayInstructions() const;
	void displayGameOver();
	void displayGameWon();
	//add colors...?

public:
	Game(): currentState(MENU), barrelsManager(board) {
		mario.setBoard(board);
	}
	void initGame();


	void setGameState(GameState state) {
		currentState = state;
	}

	GameState getGameState() {
		return currentState;
	}
	void run();
	void runGame();
	void pauseGame();
	//void drawBarrels();
	//void moveBarrels();
	//void barrelsActivation();
	// color function?
};

