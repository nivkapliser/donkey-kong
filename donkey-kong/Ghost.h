#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"
#include "Enemy.h"

class Ghost : public Enemy
{
	static constexpr char GHOST = 'x';
	bool ghostsMeeting = false;

public:
	Ghost() : Enemy(GHOST, true) { Enemy::setDirX(Enemy::getDirectionRandomly()); }

	void move() override;

	void switchGhostsMeeting();
	bool isFloorEnd() const;
};
