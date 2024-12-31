#include "Ghost.h"

// Function to set the barrel direction according to the floor type

bool Ghost::ghostsLocationsMap[25][80]; //static variable, must declare in cpp.

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

	//if (!pBoard->isValidMove(x + dirX, y + dirY)) {
	//	changeDir(STOP);
	//}
	ghostsLocationsMap[y][x] = false;


	if (ghostsLocationsMap[y + dirY][x + dirX] == true || getRandomIntInRange(100) >= 95)
	{
		gotoxy(x, y - 1);
		dirX = -dirX;

	}

	if (isFloorEnd()) {
		dirX = -dirX;
		dirY = 0;
	}

	if (pBoard->gravitation(x, y)) {
		dirY = 1;
	}



	x += dirX;
	y += dirY;
	ghostsLocationsMap[y][x] = true;


}

// Function to change the direction of the barrels
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
		encountered = true;
		//SOMETHING TO DO HERE
		encountered = false;
		return true;
	}

	return false;
}

// Function to activate a barrel
void Ghost::ghostActivation()
{
	if (isActive == false)
	{
		isActive = true;

	}
}

// Function to get the starting direction of the barrel randomly (left or right)
int Ghost::getDirectionRandomly() const
{
	int random_num = rand() % 2;

	if (random_num == 0)
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
