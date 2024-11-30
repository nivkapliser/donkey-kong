#include "Barrel.h"

bool Barrel::gravitation() {
	if (pBoard->getChar(x, y + 1) == ' ') {
		linesFallen++;
		isFalling = true;
		return true;
	}
	isFalling = false;
	return false;
}

bool Barrel::isValidMove() {
	for (int i = 0; i < 5; i++) {
		if (pBoard->getChar(x + dirX, y + dirY) == dontTouch[i]) {
			return false;
		}
	}
	return true;
}

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


void Barrel::move() {
	
	if (isValidMove() == false) {
		dirX = 0;
		dirY = 0;

	}
	if (gravitation()) {
		dirX = 0;
		dirY = 1;
	}

	x += dirX;
	y += dirY;

}

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
		exploding();
		break;
	case SAME:
		break;
	}
}

void Barrel::exploding()
{
	isActive = false;
	erase();
	gotoxy(x - 2, y - 2);
	std::cout << "BOOM!";
	gotoxy(x - 2, y);
	std::cout << "_\\|/_";
	Sleep(100);
	eraseBoom();
	linesFallen = 0;
}
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

/*
void Barrel::checkCollision()
{
	collideMario = true;
}
*/

void Barrel::barrelActivation()
{
	if (isActive == false)
	{
		isActive = true;
		x = START_X;
		y = START_Y;
	}

}
