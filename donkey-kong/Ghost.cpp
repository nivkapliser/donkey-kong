#include "Ghost.h"

// Function to set the barrel direction according to the floor type


void Ghost::floorDirSync()
{
	char floor_type = pBoard->getChar(x, y + 1);

	for (size_t i = 0; i < floorTypes; i++) {
		if (floor_type == floor[i]) {
			changeDir((Direction)i);
			break;
		}
	}
}

// Function to handle barrels movement logic
void Ghost::move() {

	if (isFloorEnd()) {
		dirX = -dirX;
		dirY = 0;
	}
	else if (ghostsMeeting == true)
	{
		dirX = -dirX;
		switchGhostsMeeting();
	}
	else if (getRandomIntInRange(100) >= 95)
	{
		dirX = -dirX;
	}

	x += dirX;
	y += dirY;
}

// Function to change the direction of the ghosts
void Ghost::changeDir(Direction dir) {
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


// Function to check if the barrel encounters mario
bool Ghost::checkEncounters(Mario& mario)
{
	if (mario.getX() == getX() && mario.getY() == getY()) // direct encounter
	{
		return true;
	}

	return false;
}


// function to delete soon
int Ghost::getDirectionRandomly() const
{
	if (getRandomIntInRange(1) == 0)
		return 1;
	else
		return -1;

}

bool Ghost::isFloorEnd() const
{
	if (pBoard->getChar(x + dirX, y + 1) == ' ' || pBoard->getChar(x + dirX, y + dirY) == 'Q')
		return true;
	return false;
}

void Ghost::switchGhostsMeeting() {

	if (ghostsMeeting == true)
		ghostsMeeting = false;
	else
		ghostsMeeting = true;
}
