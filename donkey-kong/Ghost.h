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


	void draw(char c) const {
		gotoxy(Enemy::getX(), Enemy::getY());
		std::cout << c;
	}


public:
	Ghost() {}
	Ghost(int _x, int _y, char _c, bool _active) : Enemy(_x, _y, _c, _active) { Enemy::setDirX(-1); }

	void switchGhostsMeeting();
	void move();
	bool isFloorEnd() const;
};
