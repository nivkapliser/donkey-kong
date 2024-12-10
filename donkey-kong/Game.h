#pragma once
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"


class Game
{
	
	static constexpr int ESC = 27; 
	static constexpr int MAX_BARRELS = 20;
	static constexpr int BARRELS_PACE = 700;
	enum GameState { MENU, RUNNING, PAUSED, GAME_OVER, GAME_WON, FINISH }; // To manage game state for better game control
	
	Board board;
	Mario mario;
	Barrel barrels[MAX_BARRELS]; // vector?
	GameState currentState = MENU;

	void initGame();
	void resetStage();
	void displayMenu();
	void displayInstructions() const;
	void displayGameOver();
	void displayGameWon();
	//add colors...?

public:
	Game(): currentState(MENU) {
		mario.setBoard(board);
		for (int i = 0; i < MAX_BARRELS; i++)
		{
			barrels[i].setBoard(board);
		}
	}

	//
	//void Game::initGame() {
	//	board.reset();
	//	mario.setBoard(board);
	//	for (int i = 0; i <= MAX_BARRELS - 1; i++)
	//	{
	//		barrels[i].setBoard(board);
	//	}
	//}

	//~Game() {}

	void setGameState(GameState state) {
		currentState = state;
	}
	GameState getGameState() {
		return currentState;
	}
	void run();
	void runGame();
	void pauseGame();
	//void barrelsManager();
	void drawBarrels();
	void moveBarrels();
	void barrelsActivation();
	// color function?
};

