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
	void run() override;
	void checkNextStage() override;
	void checkBarrelEncounters(BarrelManager& bm, Mario& mario) override;
	void checkGhostEncounters(GhostManager& gm, Mario& mario) override;
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

