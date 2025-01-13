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
#include "Hammer.h"

class Game
{
	static constexpr int ESC = 27; // ASCII value for the escape key
	static constexpr char PAULINE = '$';
	enum class GameState { MENU, RUNNING, PAUSED, RESUME, GAME_OVER, GAME_WON, NEXT_STAGE, FINISH }; // To manage game state for better game control


	MenuGraphics menuGraphics;
	Board board;
	Mario mario;
	BarrelManager barrelsManager;
	GhostManager ghostsManager;
	Hammer hammer;
	std::vector<std::string> boardFiles;
	int currentBoardIndex = 0;


	GameState currentState = GameState::MENU;


	void resetStage();
	void showMenu();
	void initGame();
	void runGame();
	void pauseGame();


public:
	Game() : currentState(GameState::MENU), ghostsManager(board, &menuGraphics), barrelsManager(board, &menuGraphics), mario(&menuGraphics, &hammer), board(&menuGraphics), hammer(){
		mario.setBoard(board);
	}

	// Function to get the game state
	GameState getGameState() const {
		return currentState;
	}

	// Function to check if mario met Pauline and won the game
	void marioMetPauline(Mario& mario) {
		if (mario.metPauline())
			currentState = GameState::GAME_WON;
	}

	void run();
	void explodeMarioAndResetStage(Mario& mario);
	void checkEncounters(BarrelManager& bm, Mario& mario); // change name
	void checkEncounters(GhostManager& gm, Mario& mario); // change name
	void checkHammer(Mario& mario, Hammer& hammer);
	void smashBarrel(BarrelManager& bm, Mario& mario);
	void smashGhost(GhostManager& gm, Mario& mario);
	//void updateLegend(); // will add lives and score update
	//void loadBoardFromFile(const std::string& fileName); // should be in board?
	bool showAndLoadBoards();
	void checkNextStage();
};