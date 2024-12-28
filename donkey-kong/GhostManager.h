#pragma once
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"
#include "MenuGraphics.h"
#include "Ghost.h"

class GhostManager
{
	static constexpr int MAX_GHOSTS = 5; // max number of barrels in a game
	static constexpr int GHOSTS_PACE = 1300; // pace at which barrels are activated

	Ghost ghosts[MAX_GHOSTS] = { Ghost() };
	MenuGraphics* menuGraphics;
	Board board;

	int sleepCount = 0; // counter to keep track of the pace of the barrels activation
	int activatedGhost = 1; // index of the next barrel to be activated
	bool encounters = false; // flag to indicate if mario has encountered a barrel

public:
	GhostManager(Board b, MenuGraphics* mg) : board(b), menuGraphics(mg) {}

	// get the encouters value
	bool getEncounters() const {
		return encounters;
	}

	// set the encouters value
	void setEncounters(bool value) {
		encounters = value;
	}

	void resetGhosts(Board& board);
	void drawGhosts(Mario& mario);
	void moveGhosts(Mario& mario);
	void ghostsActivation();

};