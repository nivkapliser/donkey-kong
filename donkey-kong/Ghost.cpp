#include "Ghost.h"

Ghost* Ghost::ghostsLocationsMap[26][80]; //static decleration


// Function to move the ghost in the game
void Ghost::move() {

	int x = getX();
	int y = getY();
	int dirX = getDirX();
	int dirY = getDirY();

	Ghost* next_location = ghostsLocationsMap[y + dirY][y + dirX];
	if (next_location != nullptr)
	{
		switchGhostsMeeting();
		next_location -> switchGhostsMeeting();
	}


	if (isFloorEnd() || ghostsMeeting == true || !(getBoard().isValidMove(getX() + dirX, getY() + dirY))) {
		setDirX(-dirX);
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
	ghostsLocationsMap[getY()][getX()] = this; //update the ghosts location table

	setX(x + dirX);
	setY(y + dirY);
}

void Ghost::erase()
{
	Enemy::erase();
	ghostsLocationsMap[getY()][getX()] = nullptr;

}

// Function to check if the ghost is at the end of the floor for direction change
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

// Function to switch the direction of the ghosts when they meet
void Ghost::switchGhostsMeeting() {

	if (ghostsMeeting == true)
		ghostsMeeting = false;
	else
		ghostsMeeting = true;
}

void Ghost :: resetGhostLocationInMap()
{
	ghostsLocationsMap[getY()][getX()] = nullptr;
}