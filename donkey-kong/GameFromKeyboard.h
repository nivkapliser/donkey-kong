#pragma once
#include "utils.h"
#include "Game.h"
#include "Steps.h"
#include "Results.h"

class GameFromKeyboard : public Game
{
	// managing the game state - maybe only in gameFromKeyboard
	enum class GameState { MENU, RUNNING, PAUSED, RESUME, GAME_OVER, GAME_WON, NEXT_STAGE, FINISH };
	GameState currentState = GameState::MENU; // the default starting state
	
	bool save = true; // not a default value. should be set in the constructor by the main argument input
	Steps steps;
	Results results;
	//int curr_itr = 0;

	void showMenu();
	void runGame() override;
	void pauseGame(); // only in game from key
	void checkNextStage() override;

public:
	GameFromKeyboard(bool _save) :Game(), save(_save) {
		results.setSave(_save);
	}

	~GameFromKeyboard() {} 

	GameState getGameState() const { return currentState; } // need?

	void run() override;
	void explodeMarioAndResetStage(Mario& mario);
	void checkBarrelEncounters(BarrelManager& bm, Mario& mario) override;
	void checkGhostEncounters(GhostManager& gm, Mario& mario) override;
	void marioMetPauline(Mario& mario) override { 
		if (mario.metPauline()) {
			currentState = GameState::GAME_WON; 
			results.addResult(getCurrItr(), Results::ResultValue::STAGE_FINISH);
		} 
	}
	void saveFiles();

};

 