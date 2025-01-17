#pragma once

/*
* This class represents a barrel in the game. the barrel can move in 4 directions: left, right, bottom and same.
* The barrel can fall down from the floor and 'explode' when it encounters with mario.
* If the barrel falls down 8 lines, it will be 'explode' and deactivated.
*/

#include <iostream>
#include "Board.h"
#include "Mario.h"
#include "Enemy.h"

class Barrel : public Enemy
{
	static constexpr int FALL_LIMIT = 8; // how many lines can a barrel fall
	static constexpr int EXPLODE_ZONE = 2; // for encountering with mario while exploding
	static constexpr char BARREL_CHAR = 'O'; // the char of the barrel

	int dk_X;
	int dk_Y;

	char floor[5] = "<>=Q";
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]); // to get the size of the floor array

	int linesFallen = 0;
	bool isFalling = false;
	bool isExploding = false;

public:
	Barrel() : Enemy(BARREL_CHAR, false, 0) {}
	
	void move() override;
	bool checkEncounters(Mario& mario) override;

	// Barrel specific functions
	bool fallingStatus() const { return isFalling; }
	void floorDirSync();
	void explode();
	bool barrelFallManager();
	void barrelActivation(); 
	void barrelDeactivation();

};


