#include "Ghost.h"


void Ghost::move() {

	int dirX = getDirX();
	int dirY = getDirY();

	if (isFloorEnd() || ghostsMeeting == true) {
		setDirX(-dirX);
		setDirY(0);
		if (ghostsMeeting == true)
			switchGhostsMeeting();
	}
	//if (ghostsMeeting == true)
	//{
	//	setDirX(-dirX);
	//	switchGhostsMeeting();
	//}
	else if (getRandomIntInRange(100) >= 95)
	{
		setDirX(-dirX);
	}

	Enemy::move();
}

bool Ghost::isFloorEnd() const
{
	int x = getX();
	int dirX = getDirX();
	int y = getY();
	int dirY = getDirY();

	if (getBoard().getChar(x + dirX, y + 1) == ' ' || getBoard().getChar(x + dirX, y + dirY) == 'Q')
		return true;
	return false;
}

void Ghost::switchGhostsMeeting() {

	if (ghostsMeeting == true)
		ghostsMeeting = false;
	else
		ghostsMeeting = true;
}

//void Ghost::placeRandomly(Board& board) {
//	int x, y;
//
//	srand(time(0));
//	do {
//		x = rand() % Board::getMaxX();
//		y = rand() % Board::getMaxY();
//	} while (!board.isFloor(x, y + 1) || board.getChar(x, y) != ' ');  // Place on floor space
//
//	setX(x);
//	setY(y);
//}