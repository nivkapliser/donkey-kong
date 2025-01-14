#pragma once

/*
* This class represents a barrel in the game. the barrel can move in 4 directions: left, right, bottom and same.
* The barrel can fall down from the floor and 'explode' when it encounters with mario.
* If the barrel falls down 8 lines, it will be 'explode' and deactivated.
*/

#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Mario.h"
#include "Enemy.h"

class Barrel : public Enemy
{
	static constexpr int START_X_R = 38; // for barrels that start from the right
	static constexpr int START_X_L = 36; // for barrels that start from the left
	static constexpr int START_Y = 7; 
	static constexpr int FALL_LIMIT = 8; // how many lines can a barrel fall
	static constexpr int EXPLODE_ZONE = 2; // for encountering with mario
	int dk_X;
	int dk_Y;

	char floor[5] = "<>=Q";
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]); // to get the size of the floor array

	

	int linesFallen = 0;
	bool isFalling = false;
	bool isExploding = false;

public:
	Barrel() : Enemy('O', false, START_Y) {}//????

	// Function to check if the barrel is falling
	bool fallingStatus() const {
		return isFalling;
	}
	
	void move();
	void floorDirSync();
	void printBoom();
	void explode();
	bool barrelFallManager();
	void barrelActivation(); 
	void barrelDeactivation();
	void eraseBoom() const;
	bool checkEncounters(Mario& mario); // should be virtual 
	//bool reachedBottom();
};


