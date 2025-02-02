#pragma once
#include "Game.h"
#include "Steps.h"
#include "Results.h"

/*
* This class represent a game played from the keyboard. it can be played regularly or in a save mode.
* If in save mode, the game will save the steps and results to files for feauture play.
*/

class GameFromFile : public Game
{
	static constexpr int SLEEP_TIME = 10;
	static constexpr int SLEEP_IN_SILENT = 0; // no sleep in silent mode

	Steps steps;
	Results results;
	
	void runGame() override;
	bool showAndLoadBoards() override;
	int final_board = -1;

public:
	GameFromFile(bool _silent) : Game() {
		setSilent(_silent);
		getBoard().setSilent(_silent);
	}
	~GameFromFile() {}

	void run() override;
	void checkNextStage() override;
	bool checkEnemyEncounters(EnemiesManager& em, Mario& mario) override;
	bool marioMetPauline(Mario& mario) override;
	void reportResultError(const std::string& message, const std::string& filename, size_t iteration);
	int getFinalBoard() { return final_board; }
	void setFinalBoard(int board) { final_board = board; }

};

