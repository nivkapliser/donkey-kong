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
	static Ghost* ghostsLocationsMap[26][80]; // for ghost meeting


	bool ghostsMeeting = false;	// flag to indicate if the ghosts are meeting (for direction change)

public:
	Ghost() : Enemy(GHOST, true) { Enemy::setDirX(Enemy::getDirectionRandomly()); }

	void move() override;
	void erase() override;
	// Ghosts specific functions
	//void setIndex(int i) { ghostIndex = i; }
	void switchGhostsMeeting();
	bool isFloorEnd() const;
	void resetGhostLocationInMap() {ghostsLocationsMap[getY()][getX()] = nullptr;}
	void reset(Board& board) override; //shold be virtual
	void setGhostInLocationMap() { ghostsLocationsMap[getY()][getX()] = this; }
	void deactivation() override;
};
