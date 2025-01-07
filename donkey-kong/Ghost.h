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
	Ghost() : Enemy('x', true) { Enemy::setDirX(Enemy::getDirectionRandomly()); }
	//Ghost(int _x, int _y, char _c, bool _active) : Enemy(_x, _y, _c, _active) { 
	//	placeRandomly(Enemy::getBoard()); //?
	//	setDirX(-1);
	//}

	void switchGhostsMeeting();
	void move();
	bool isFloorEnd() const;
	void placeRandomly(Board& board);
};
