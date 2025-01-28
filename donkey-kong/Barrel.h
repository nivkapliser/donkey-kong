#pragma once
#include "Enemy.h"

/*
* This class represents a barrel in the game. the barrel can move in 4 directions: left, right, bottom and same.
* The barrel can fall down from the floor and 'explode' when it encounters with mario.
* If the barrel falls down 8 lines, it will be 'explode' and deactivated.
* The barrel is mario's enemy and so it inherits from the Enemy class.
*/

class Barrel : public Enemy
{
	static constexpr int FALL_LIMIT = 8;      // how many lines can a barrel fall in a row before exploding
	static constexpr int EXPLODE_ZONE = 2;    // for encountering with mario while exploding
	static constexpr char BARREL_CHAR = 'O';  // the char of the barrel

	int dk_X; // for init the barrel position
	int dk_Y; // for init the barrel position

	// the floor types that the barrel can move on for directions sync
	char floor[5] = "<>=Q";
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]); 

	// state variables to manage barrel falling and exploding
	int linesFallen = 0;
	bool isFalling = false;
	bool isExploding = false;

public:
	Barrel() : Enemy(BARREL_CHAR, false, 0) {}
	
	void move() override;
	bool checkEncounters(Mario& mario) override;
	void deactivation() override;
	void activation(bool _active) override { Enemy::activation(_active); }
	void reset(Board& board) override { setBoard(board); }

	// Barrel specific functions
	bool fallingStatus() const { return isFalling; }
	void floorDirSync();
	void explode();
	bool barrelFallManager();
	void barrelActivation(); 
};


