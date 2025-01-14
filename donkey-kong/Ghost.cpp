#include "Ghost.h"


void Ghost::move() {

	int x, y;
	int dirX = getDirX();
	int dirY = getDirY();

	if (isFloorEnd() || ghostsMeeting == true) {
		setDirX(-dirX);
		//setDirY(0);
		if (ghostsMeeting == true)
			switchGhostsMeeting();
	}
	else if (getRandomIntInRange(100) >= 95)
	{
		setDirX(-dirX);
	}

	if (getBoard().gravitation(getX(), getY(), getDirX()))
		setDirY(1);
	else
		setDirY(0);

	dirX = getDirX();
	dirY = getDirY();
	x = getX();
	y = getY();
	setX(x + dirX);
	setY(y + dirY);
}

bool Ghost::isFloorEnd() const
{
	int x = getX();
	int dirX = getDirX();
	int y = getY();
	int dirY = getDirY();

	if (getBoard().getChar(x + dirX, y + 1) == ' ' || getBoard().getChar(x + dirX, y + dirY) == getBoard().getLetter("WALL") || !getBoard().isValidMove(x + dirX, y + dirY))
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