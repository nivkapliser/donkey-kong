#pragma once
#include "utils.h"
#include "Game.h"
#include "Steps.h"
#include "Results.h"

/*
* This class represent a game played from a file. it can be played regularly or in a silent mode.
* When played regularly, the game will read the steps and results from files and play the game accordingly.
* If in silent mode, the game will not display the game graphics and will run faster. 
* In both modes, the game will check the steps and results files for errors.
*/

class GameFromKeyboard : public Game
{
	// managing the game state - maybe only in gameFromKeyboard
	enum class GameState { MENU, RUNNING, PAUSED, RESUME, GAME_OVER, GAME_WON, NEXT_STAGE, FINISH };
	GameState currentState = GameState::MENU; // the default starting state
	
	bool save = true; 
	Steps steps;
	Results results;

	void showMenu();
	void runGame() override;
	void pauseGame();
	void checkNextStage() override;

public:
	GameFromKeyboard(bool _save) :Game(), save(_save) {
		results.setSave(_save);
	}
	~GameFromKeyboard() {} 

	void run() override;
	void explodeMarioAndResetStage(Mario& mario);
	bool checkEnemyEncounters(EnemiesManager& em, Mario& mario) override;
	bool marioMetPauline(Mario& mario) override;
	GameState getGameState() const { return currentState; }
	void saveFiles();
};

 