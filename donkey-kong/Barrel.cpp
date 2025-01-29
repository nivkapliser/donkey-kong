#include "Barrel.h"

// Function to set the barrel direction according to the floor type
void Barrel::floorDirSync()
{
	char floor_type = getBoard().getChar(getX(), getY() + 1);
	for (size_t i = 0; i < floorTypes; i++) {
		if (floor_type == floor[i]) {
			changeDir(Direction(i));
			break;
		}
	}
}

// Function to handle barrels movement logic
void Barrel::move() {
	int x = getX(), y = getY();
	int dirX = getDirX(), dirY = getDirY();

	if (reachedBottom()) {
		explode();
		return;
	}

	// if next move is invalid (floor or wall) change direction
	if (!getBoard().isValidMove(x + dirX, y + dirY) || 
		getBoard().getChar(x + 2 * dirX, y + dirY) == getBoard().getLetter("WALL")) { 
		setDirX(-dirX);
	}

	floorDirSync();
	
	// to handle gravitation
	if (getBoard().gravitation(getX(), getY(), getDirX())) {
		setDirY(1);
		linesFallen++;
		isFalling = true;
	}
	else {
		isFalling = false;
	}

	if (barrelFallManager()) {
		explode();
	}

	setY(getY() + getDirY());
	setX(getX() + getDirX());
}

// Function to explode the barrel 
void Barrel::explode()
{
	bool isSilent = getBoard().getSilent();
	isExploding = true;
	
	erase();
	if (isEncountered() && !isSilent)
		printAnimation("BOOM!", "_\\|/_", 700);
	else
		if (!isSilent) printAnimation("BOOM!", "_\\|/_", 25);

	deactivation();
	linesFallen = 0;
}


// Function to check if the barrel has fallen enough lines
bool Barrel::barrelFallManager()
{
	if (isFalling == false && linesFallen >= FALL_LIMIT)
		return true;
	else if (isFalling == false && linesFallen < FALL_LIMIT)
	{
		linesFallen = 0;
		return false;
	}
	return false;
}

// Function to check if the barrel encounters mario
bool Barrel::checkEncounters(Mario& mario)
{
	if (mario.getSmash() && mario.getHammer()->isCollected()) {
		return false;
	}
	// direct encounter
	if (mario.getX() == getX() && mario.getY() == getY()) 
	{
		setEncountered(true);
		explode();
		setEncountered(false);
		return true;
	}
	// indirect encounter (2 chars away)
	else if ((abs(mario.getX() - getX()) <= EXPLODE_ZONE && mario.getY() == getY()) && isExploding) 
	{	
		return true;	
	}
	return false;
}

// Function to activate a barrel
void Barrel::barrelActivation() 
{
	if (!checkActivationStatus())
	{
		isExploding = false;
		activation(true);
		if (getDirectionRandomly() == 1)
			setX(getBoard().getDonkeyKongX() + 1); // for the start position of the barrel
		else
			setX(getBoard().getDonkeyKongX() - 1); // for the start position of the barrel
		setY(getBoard().getDonkeyKongY());
	}
}

// Function to deactivate a barrel
void Barrel::deactivation() {
	activation(false);
	linesFallen = 0;
	setEncountered(false);
}
