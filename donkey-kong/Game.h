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
	static constexpr char PAULINE = '$';

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
	long random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());

protected:
	// some internal use functions to manage the game flow
	void resetStage();
	//void showMenu(); // only in game from key
	void initGame();
	virtual void runGame() = 0; // virtual
	//void pauseGame(); // only in game from key
	virtual void checkNextStage() = 0; // virtual?
	virtual bool showAndLoadBoards(); // need to split into load and show 

public:
	// game state should be something else
	Game() : ghostsManager(board, &menuGraphics),
		barrelsManager(board, &menuGraphics), mario(&menuGraphics, &hammer),
		board(&menuGraphics), hammer(), spacialGhost(&mario)
	{
		mario.setBoard(board);
	}
	
	// ~Game() = default; // for virtual

	virtual void run() = 0; // virtual
	//GameState getGameState() const { return currentState; } // keyboard
	void explodeMarioAndResetStage(Mario& mario); // both
	virtual void checkBarrelEncounters(BarrelManager& bm, Mario& mario) = 0; // both
	virtual void checkGhostEncounters(GhostManager& gm, Mario& mario) = 0; // both 
	void checkHammer(Mario& mario, Hammer& hammer); // both
	void smashBarrel(BarrelManager& bm, Mario& mario); // both 
	void smashGhost(GhostManager& gm, Mario& mario); // both
	void marioHit(); // both
	//void marioMetPauline(Mario& mario) { // both?
	//	if (mario.metPauline())
	//		currentState = GameState::GAME_WON;
	//}

	Mario& getMario() { return mario; } 
	BarrelManager& getBarrelManager() { return barrelsManager; }
	GhostManager& getGhostManager() { return ghostsManager; }
	Board& getBoard() { return board; }
	SpacialGhost& getSpacialGhost() { return spacialGhost; }
	Hammer& getHammer() { return hammer; }
	MenuGraphics& getMenuGraphics() { return menuGraphics; }
	std::vector<std::string>& getBoards() { return boardFiles; }
	int getCurrBoardIndex() { return currentBoardIndex; }
	void setCurrentBoardIndex(int index) { currentBoardIndex = index; }

};