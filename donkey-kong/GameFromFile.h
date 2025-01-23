#pragma once
#include "Game.h"
#include "Steps.h"

class GameFromFile : public Game
{
	Steps steps;
	void runGame() override;
public:
	void run() override;
	void checkNextStage() override;
	void checkBarrelEncounters(BarrelManager& bm, Mario& mario) override;
	void checkGhostEncounters(GhostManager& gm, Mario& mario) override;
};

