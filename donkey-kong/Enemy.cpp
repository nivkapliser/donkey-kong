#include "Enemy.h"

// Function to change the direction of the enemy
void Enemy::changeDir(Direction dir) {
	switch (dir) {
	case Direction::LEFT:
		dirY = 0;
		dirX = -1;
		break;
	case Direction::RIGHT:
		dirY = 0;
		dirX = 1;
		break;
	case Direction::STOP:
		dirX = 0;
		dirY = 0;
		break;
	case Direction::SAME:
		dirY = 0;
		break;
	}
}

// Function to get random direction for the enemy
int Enemy::getDirectionRandomly() const {

	if (getRandomIntInRange(1) == 0)
		return 1;
	else
		return -1;

}

// Function to check if the enemy has reached the bottom floor
bool Enemy::reachedBottom()
{
	if (getBoard().getChar(getX(), getY() + 1) == getBoard().getLetter("WALL") ||
		getY() >= getBoard().getDimension('Y') - 1)
		return true;
	return false;
}

// Function to print animation (for exploding and encountering)
void Enemy::printAnimation (const char* upper, const char* under, int sleep)
{
	gotoxy(getX() - 2, getY() - 2);
	std::cout << upper;
	gotoxy(getX() - 2, getY());
	std::cout << under;
	Sleep(sleep);
	eraseAnimation(upper, under);
}

// Function to erase animation
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

