#include "Enemy.h"


void Enemy::changeDir(Direction dir) {
	switch (dir) {
	case LEFT:
		dirY = 0;
		dirX = -1;
		break;
	case RIGHT:
		dirY = 0;
		dirX = 1;
		break;
	case STOP:
		dirX = 0;
		dirY = 0;
		break;
	case SAME:
		dirY = 0;
		break;
	}
}

bool Enemy::checkEncounters(Mario& mario) {
	if (mario.getX() == getX() && mario.getY() == getY()) // direct encounter
	{
		return true;
	}
	return false;
}

int Enemy::getDirectionRandomly() const {

	if (getRandomIntInRange(1) == 0)
		return 1;
	else
		return -1;

}
