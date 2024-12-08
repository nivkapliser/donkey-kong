#pragma once
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"

class BarrelManager
{
	static constexpr int MAX_BARRELS = 10;
	static constexpr int BARRELS_PACE = 1500;

	Barrel barrels[MAX_BARRELS];

public:
	BarrelManager(Board& board) {
		for (int i = 0; i < MAX_BARRELS; i++)
		{
			barrels[i].setBoard(board);
		}
	}

	void resetBarrels(Board& board);
	void drawBarrels(Mario& mario);
	void moveBarrels(Mario& mario);
	void barrelsActivation();
};

