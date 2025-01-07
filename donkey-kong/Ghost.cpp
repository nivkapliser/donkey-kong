#include "Ghost.h"


void Ghost::move() {

	int dirX = Enemy::getDirX();
	int dirY = Enemy::getDirY();

	if (isFloorEnd()) {
		Enemy::setDirX(-dirX);
		Enemy::setDirY(0);
	}
	else if (ghostsMeeting == true)
	{
		Enemy::setDirX(-dirX);
		switchGhostsMeeting();
	}
	else if (getRandomIntInRange(100) >= 95)
	{
		Enemy::setDirX(-dirX);
	}

	Enemy::move();
}

bool Ghost::isFloorEnd() const
{
	int x = Enemy::getX();
	int dirX = Enemy::getDirX();
	int y = Enemy::getY();
	int dirY = Enemy::getDirY();

	if (Enemy::getBoard().getChar(x + dirX, y + 1) == ' ' || Enemy::getBoard().getChar(x + dirX, y + dirY) == 'Q')
		return true;
	return false;
}

void Ghost::switchGhostsMeeting() {

	if (ghostsMeeting == true)
		ghostsMeeting = false;
	else
		ghostsMeeting = true;
}

void Ghost::placeRandomly(Board& board) {
	int x, y;

	srand(time(0));
	do {
		x = rand() % Board::getMaxX();
		y = rand() % Board::getMaxY();
	} while (!board.isFloor(x, y + 1) || board.getChar(x, y) != ' ');  // Place on floor space

	setX(x);
	setY(y);
}