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

bool Enemy::checkEncounters(Mario& mario) { // virtual?
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

void Enemy::printAnimation (const char* upper, const char* under, int sleep) // need to handle print on forbidden chars
{
	gotoxy(getX() - 2, getY() - 2);
	std::cout << upper;
	gotoxy(getX() - 2, getY());
	std::cout << under;
	Sleep(sleep);
	eraseAnimation(upper, under);
}
void Enemy::eraseAnimation(const char* upper, const char* under)
{
	char lastchar;
	int upper_len = strlen(upper);
	int under_len = strlen(under);
	for (int i = 0; i <= upper_len; i++)
	{
		lastchar = getBoard().getChar(getX() - 2 + i, getY() - 2);
		gotoxy(getX() - 2 + i, getY() - 2);
		std::cout << lastchar;
	}
	for (int i = 0; i <= under_len; i++)
	{
		lastchar = getBoard().getChar(getX() - 2 + i, getY());
		gotoxy(getX() - 2 + i, getY());
		std::cout << lastchar;
	}

}

