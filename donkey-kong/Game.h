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
#include "EnemiesManager.h"


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
	Hammer hammer;
	EnemiesManager enemiesManager;

	// managing the game boards
	std::vector<std::string> boardFiles;
	int currentBoardIndex = 0;
	long random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	int curr_itr = 0;
	bool silent = false; // need to handle not load mode
	 
protected:
	// some internal use functions to manage the game flow
	void resetStage();
	void initGame();
	virtual void runGame() = 0; // virtual
	virtual void checkNextStage() = 0; // virtual?
	virtual bool showAndLoadBoards(); // need to split into load and show 
public:
	// game state should be something else
	Game() : mario(&menuGraphics, &hammer), board(&menuGraphics), 
		hammer(), enemiesManager(board, &menuGraphics, &mario) {
		mario.setBoard(board);
	}
	
	// ~Game() = default; // for virtual

	virtual void run() = 0; // virtual
	void explodeMarioAndResetStage(Mario& mario); // both
	virtual void checkEnemyEncounters(EnemiesManager& em,Mario& mario) = 0;
	void checkHammer(Mario& mario, Hammer& hammer); // both
	void smashEnemy(EnemiesManager& em, Mario& mario);
	void marioHit(); // both
	virtual void marioMetPauline(Mario& mario) = 0;
	
	Mario& getMario() { return mario; } 
	EnemiesManager& getEnemiesManager() { return enemiesManager; }
	Board& getBoard() { return board; }
	Hammer& getHammer() { return hammer; }
	MenuGraphics& getMenuGraphics() { return menuGraphics; }
	std::vector<std::string>& getBoards() { return boardFiles; }
	int getCurrBoardIndex() { return currentBoardIndex; }
	void setCurrentBoardIndex(int index) { currentBoardIndex = index; }
	void setRandomSeed(int seed) { random_seed = seed; }
	long getRandomSeed() const { return random_seed; }
	int getCurrItr() const { return curr_itr; }
	void setCurrItr(int itr) { curr_itr = itr; }
	void setSilent(bool s) { silent = s; }
	bool getSilent() const { return silent; }
};