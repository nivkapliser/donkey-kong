#pragma once
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"

class BarrelManager
{
	static constexpr int MAX_BARRELS = 10;
	static constexpr int BARRELS_PACE = 1500;

	Barrel barrels[MAX_BARRELS];

	bool encounters = false;

public:
	BarrelManager(Board& board) { // move to cpp
		for (int i = 0; i < MAX_BARRELS; i++)
		{
			barrels[i].setBoard(board);
		}
	}

	void resetBarrels(Board& board);
	void drawBarrels(Mario& mario);
	void moveBarrels(Mario& mario);
	void barrelsActivation();
	bool getEncounters() const {
		return encounters;
	}
	void setEncounters(bool value) {
		encounters = value;
	}
};

