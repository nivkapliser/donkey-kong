#include "Barrel.h"

bool Barrel::gravitation() {
	if (pBoard->getChar(x, y + 1) == ' ') {
		return true;
	}
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
		isActive = false;
		exploding();
		break;
	case SAME:
		break;
	}
}

void Barrel::exploding()
{
	erase();
	gotoxy(x - 2, y - 2);
	std::cout << "BOOM!";
	gotoxy(x - 2, y);
	std::cout << "_\|/_";
	Sleep(100);
	gotoxy(x - 2, y - 2);
	std::cout << "     ";
	gotoxy(x - 2, y);
	std::cout << "     ";
}
