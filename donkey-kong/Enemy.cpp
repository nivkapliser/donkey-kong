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
bool Enemy::reachedBottom()
{
	if (getBoard().getChar(getX(), getY() + 1) == getBoard().getLetter("WALL") || getY() >= 24) //change 24 to (MAX_Y - 1)
		return true;
	return false;
}

//bool Enemy::onFloor()
//{
//	char under = getBoard().getChar(getX(), getY() + 1);
//	char floor[4] = "<>=";
//
//	if (under == getBoard().getLetter("WALL") || getY() >= 24) //change 24 to (MAX_Y - 1)
//		return true;
//	for (int i = 0; i < 3; i++)
//		if (under == floor[i])
//			return true;
//	return false;
//}
