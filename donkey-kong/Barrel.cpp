#include "Barrel.h"

// Function to set the barrel direction according to the floor type
void Barrel::floorDirSync()
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
void Barrel::move() {
	
	if (!pBoard->isValidMove(x + dirX, y + dirY)) {
		dirX = 0;
		dirY = 0;

	}
	if (pBoard->gravitation(x, y)) {
		dirX = 0;
		dirY = 1;
	}

	x += dirX;
	y += dirY;

}

// Function to change the direction of the barrels
void Barrel::changeDir(Direction dir) {
	switch (dir) {
	case LEFT:
		dirY = 0;
		dirX = -1;
		break;
	case RIGHT:
		dirY = 0;
		dirX = 1;
		break;
	case BOTTOM:
		explode();
		break;
	case SAME:
		break;
	}
}

// Function to explode the barrel 
void Barrel::explode()
{
	isExploding = true;
	isActive = false;
	erase();
	gotoxy(x - 2, y - 2);
	std::cout << "BOOM!";
	gotoxy(x - 2, y);
	std::cout << "_\\|/_";
	Sleep(50);//???
	eraseBoom();
	linesFallen = 0;
}

// Function to erase the explosion
void Barrel::eraseBoom()
{
	char lastchar;
	for (int i = 0; i <= 5; i++)
	{
		lastchar = pBoard->getChar(x - 2 + i, y - 2);
		gotoxy(x - 2 + i, y - 2);
		std::cout << lastchar;
		lastchar = pBoard->getChar(x - 2 + i, y);
		gotoxy(x - 2 + i, y);
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
	if (mario.getX() == getX() && mario.getY() == getY())
	{
		explode();
		return true;
	}
	else if ((abs(mario.getX() - getX()) <= EXPLODE_ZONE && mario.getY() == getY()) && isExploding)
		return true;
	return false;
}

// Function to activate a barrel
void Barrel::barrelActivation()
{
	if (isActive == false)
	{
		isExploding = false;
		isActive = true;
		x = START_X;
		y = START_Y;
	}

}
