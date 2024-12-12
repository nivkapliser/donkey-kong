#pragma once

/*
* This class is responsible for managing the barrels in the game.
* It is responsible for drawing, moving, and activating the barrels.
* It also checks for collisions between the barrels and mario.
*/

#include "Board.h"
#include "Mario.h"
#include "Barrel.h"

class BarrelManager
{
	static constexpr int MAX_BARRELS = 20; // max number of barrels in a game
	static constexpr int BARRELS_PACE = 700; // pace at which barrels are activated

	Barrel barrels[MAX_BARRELS]; 

	int sleepCount = 0; // counter to keep track of the pace of the barrels activation
	int activatedBarrel = 1; // index of the next barrel to be activated
	bool encounters = false; // flag to indicate if mario has encountered a barrel

public:
	BarrelManager(Board& board) { // move to cpp
		for (int i = 0; i < MAX_BARRELS; i++)
		{
			barrels[i].setBoard(board); // need to start the barrels first?
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

