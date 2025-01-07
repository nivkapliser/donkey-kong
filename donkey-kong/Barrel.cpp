#include "Barrel.h"


// Function to set the barrel direction according to the floor type
void Barrel::floorDirSync()
{
	char floor_type = getBoard().getChar(getX(), getY() + 1);

	for (size_t i = 0; i < floorTypes; i++) {
		if (floor_type == floor[i]) {
			changeDir(Direction(i));  //was changeDir((Direction)i);

			break;
		}
	}
}

// Function to handle barrels movement logic
void Barrel::move() {
	
	if (!getBoard().isValidMove(getX() + getDirX(), getY() + getDirY())) {
		changeDir(STOP);
	}

	if (getBoard().gravitation(getX(), getY())) {
		setDirY(1);
		linesFallen++;
		isFalling = true;
	}
	else
		isFalling = false;
	Enemy::move();
}

// Function to print the explosion effect
void Barrel::printBoom() {
	gotoxy(getX() - 2, getY() - 2);
	std::cout << "BOOM!";
	gotoxy(getX() - 2, getY());
	std::cout << "_\\|/_";
}

// Function to explode the barrel 
void Barrel::explode()
{
	isExploding = true;
	activation(false);
	erase();
	printBoom();
	if(isEncountered() == true)
		Sleep(700); // longer Sleep time for visual effect
	else
		Sleep(25);

	eraseBoom();
	linesFallen = 0;
}

// Function to erase the explosion
void Barrel::eraseBoom() const
{
	char lastchar;
	for (int i = 0; i <= 5; i++)
	{
		lastchar = getBoard().getChar(getX() - 2 + i, getY() - 2);
		gotoxy(getX() - 2 + i, getY() - 2);
		std::cout << lastchar;
		lastchar = getBoard().getChar(getX() - 2 + i, getY());
		gotoxy(getX() - 2 + i, getY());
		std::cout << lastchar;
	}
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
	if (Enemy::checkEncounters(mario)) // direct encounter
	{
		setEncountered(true);
		explode();
		setEncountered(false);
		return true;
	}
	else if ((abs(mario.getX() - getX()) <= EXPLODE_ZONE && mario.getY() == getY()) && isExploding) // indirect encounter (2 chars away)
		return true;
	return false;
}

// Function to activate a barrel
void Barrel::barrelActivation()
{
	if (isActive() == false)
	{
		isExploding = false;
		activation(true);
		if (getDirectionRandomly() == 1)
			setX(START_X_L);
		else
			setX(START_X_R);
	}
}
void Barrel::barrelDeactivation() {
	activation(false);
	linesFallen = 0;
	isExploding = false;
	setEncountered(false);
}

// Function to get the starting direction of the barrel randomly (left or right)
