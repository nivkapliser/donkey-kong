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
	int x = getX();
	int y = getY();
	int dirX = getDirX();
	int dirY = getDirY();

	if (reachedBottom()) {
		explode();
		return;
	}

		

	// if next move is invalid (floor or wall) change direction
	if (!getBoard().isValidMove(x + dirX, y + dirY) || getBoard().getChar(x + 2 * dirX, y + dirY) == getBoard().getLetter("WALL")) { // wall can be enum 
		setDirX(-dirX);
	}

	// to handle gravitation
	if (getBoard().gravitation(x, y, getDirX())) {
		setDirY(1);
		linesFallen++;
		isFalling = true;
	}
	else {
		isFalling = false;
	}

	setY(y + dirY);
	setX(x + dirX);
}

// Function to print the explosion effect
//void Barrel::printBoom() {
//	gotoxy(getX() - 2, getY() - 2);
//	std::cout << "BOOM!";
//	gotoxy(getX() - 2, getY());
//	std::cout << "_\\|/_";
//}

// Function to explode the barrel 
void Barrel::explode()
{
	isExploding = true;
	
	erase();
	if (isEncountered())
		printAnimation("BOOM!", "_\\|/_", 700);
	else
		printAnimation("BOOM!", "_\\|/_", 25);

	barrelDeactivation();
	linesFallen = 0;
}

// Function to erase the explosion
//void Barrel::eraseBoom() const
//{
//	char lastchar;
//	for (int i = 0; i <= 5; i++)
//	{
//		lastchar = getBoard().getChar(getX() - 2 + i, getY() - 2);
//		gotoxy(getX() - 2 + i, getY() - 2);
//		std::cout << lastchar;
//		lastchar = getBoard().getChar(getX() - 2 + i, getY());
//		gotoxy(getX() - 2 + i, getY());
//		std::cout << lastchar;
//	}
//}

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
	if (mario.getX() == getX() && mario.getY() == getY()) // direct encounter
	{
		setEncountered(true);
		explode();
		setEncountered(false);
		return true;
	}
	else if ((abs(mario.getX() - getX()) <= EXPLODE_ZONE && mario.getY() == getY()) && isExploding) // indirect encounter (2 chars away)
	{
		setEncountered(true);	// check
		//explode();	
		//setEncountered(false);	
		return true;	
	}
	return false;
}

// Function to activate a barrel
void Barrel::barrelActivation() // need to make more generic
{
	if (!checkActivationStatus())
	{
		isExploding = false;
		activation(true);
		if (getDirectionRandomly() == 1)
			setX(getBoard().getDonkeyKongX() + 1);
		else
			setX(getBoard().getDonkeyKongX() - 1);
		setY(getBoard().getDonkeyKongY());
	}
}
void Barrel::barrelDeactivation() {
	activation(false);
	linesFallen = 0;
	//isExploding = false;
	setEncountered(false);
}
