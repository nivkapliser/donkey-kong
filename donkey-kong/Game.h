#pragma once
#include "utils.h"
#include "Board.h"
#include "Mario.h"
#include "BarrelManager.h"
#include "Barrel.h"
#include "MenuGraphics.h"
#include "Ghost.h"
#include "GhostManager.h"
#include "Hammer.h"
#include "SpacialGhost.h"

/*
* This class is the main class of the game. It manages the game state, flow, and controls the game loop.
* It also initializes the game and handles user input.
* It is responsible for the game logic and the interactions between the game entities.
*/

class Game
{
	static constexpr int ESC = 27; 
	static constexpr char PAULINE = '$';

	// managing the game state
	enum class GameState { MENU, RUNNING, PAUSED, RESUME, GAME_OVER, GAME_WON, NEXT_STAGE, FINISH }; 
	GameState currentState = GameState::MENU; // the default starting state

	// game entities
	MenuGraphics menuGraphics;
	Board board;
	Mario mario;
	BarrelManager barrelsManager;
	GhostManager ghostsManager;
	Hammer hammer;

	SpacialGhost spacialGhost; // for debug - latter will be in a manager class 

	// managing the game boards
	std::vector<std::string> boardFiles;
	int currentBoardIndex = 0;
	
	// some internal use functions to manage the game flow
	void resetStage();
	void showMenu();
	void initGame();
	void runGame();
	void pauseGame();
	void checkNextStage();
	bool showAndLoadBoards();

public:
	Game() : currentState(GameState::MENU), ghostsManager(board, &menuGraphics),
		barrelsManager(board, &menuGraphics), mario(&menuGraphics, &hammer),
		board(&menuGraphics), hammer(), spacialGhost(&mario)
	{
		mario.setBoard(board);
	}
	
	void run(); 
	GameState getGameState() const { return currentState; }
	void explodeMarioAndResetStage(Mario& mario);
	void checkBarrelEncounters(BarrelManager& bm, Mario& mario); 
	void checkGhostEncounters(GhostManager& gm, Mario& mario); 
	void checkHammer(Mario& mario, Hammer& hammer);
	void smashBarrel(BarrelManager& bm, Mario& mario);
	void smashGhost(GhostManager& gm, Mario& mario);
	void marioHit();
	void marioMetPauline(Mario& mario) {
		if (mario.metPauline())
			currentState = GameState::GAME_WON;
	}
};