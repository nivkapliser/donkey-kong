#pragma once
#include "Enemy.h"

/*
* This class represents a ghost in the game. the ghost is a type of enemy that moves in a random direction.
* The ghost can't fall down from the floor and it kill's mario when encounters him.
* The ghost will change its direction when it meets another ghost.
*/

class Ghost : public Enemy
{
	static constexpr char GHOST = 'x';

	bool ghostsMeeting = false;	// flag to indicate if the ghosts are meeting (for direction change)

public:
	Ghost() : Enemy(GHOST, true) { Enemy::setDirX(Enemy::getDirectionRandomly()); }

	void move() override;

	// Ghosts specific functions
	void switchGhostsMeeting();
	bool isFloorEnd() const;
};
