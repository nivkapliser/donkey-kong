#pragma once
#include "Game.h"
#include "Steps.h"
#include "Results.h"

class GameFromFile : public Game
{
	Steps steps;
	Results results;
	
	void runGame() override;
	bool showAndLoadBoards() override;
public:
	GameFromFile(bool _silent) : Game() {
		setSilent(_silent);
		getBoard().setSilent(_silent);
	}
	~GameFromFile() {}
	void run() override;
	void checkNextStage() override;
	void checkEnemyEncounters(EnemiesManager& em, Mario& mario) override;
	void reportResultError(const std::string& message, const std::string& filename, size_t iteration);
	void marioMetPauline(Mario& mario) override {
		if (mario.metPauline()) {
			if (results.popResult().second != results.ResultValue::STAGE_FINISH) {
				reportResultError("Result file does not match finish stage", getBoard().getBoardName(), getCurrItr());
			}
			checkNextStage();	
		}
	}
};

