#include "Mario.h"



bool Mario::isLadder() {
	if (pBoard->getChar(x, y - 1) == 'H' || pBoard->getChar(x, y + 1) == 'H') {
		return true;
	}
	return false;
}

void Mario::climbLadder() {
	dirY = -1;
	dirX = 0;
	while (isLadder() == true)
	{
		x += dirX;
		y += dirY;
		draw();
		gotoxy(x, y + 1);
		std::cout << 'H';
		Sleep(175);
		erase();
	}	
	changeDir(STAY);
}

void Mario::downLadder() {
	dirY = 1;
	dirX = 0;
	while (isLadder() == true)
	{
		x += dirX;
		y += dirY;
		draw();
		gotoxy(x, y - 1);
		std::cout << 'H';
		Sleep(175);
		erase();
	}
	changeDir(STAY);
}

bool Mario::gravitation() {
	if (pBoard->getChar(x, y + 1) == ' ' && isJump == false) {
		return true;
	}
	return false;
}

bool Mario::isValidMove() {
	for (int i = 0; i < 5; i++) {
		if (pBoard->getChar(x + dirX, y + dirY) == dontTouch[i]) {
			//changeDir(STAY);
			return false;
		}
	}
	return true;
}

void Mario::jump() {

	isJump = true;
	dirY = -1;
	for (int i = 0; i < 2; i++) {
		Sleep(100);
		erase();
		move();
		draw();
	}
	dirY = 1;
	for (int i = 0; i < 2; i++) {
		Sleep(100);
		erase();
		move();
		draw();
	}
	dirY = 0;
	isJump = false;
	

}

void Mario::changeDir(Direction dir) {
	switch (dir) {
	case LEFT:
		dirY = 0;
		dirX = -1;
		break;
	case UP:
		if (isLadder()) {
			climbLadder();
		}
		else {
			jump();
		}
		break;
	case RIGHT:
		dirY = 0;
		dirX = 1;
		break;
	case DOWN:
		if (isLadder()) {
			downLadder();
		}
		else {
			dirY = 1;
			dirX = 0;
		}
		break;
	case STAY:
		dirY = 0;
		dirX = 0;
		break;
	}
}

void Mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			changeDir((Direction)i);
		}
	}
}

void Mario::move() {


	//if (pBoard->getChar(x + dirX, y + dirY) == 'Q') {
	//	changeDir(STAY);
	//}
	//if (pBoard->getChar(x + dirX, y + dirY) == '<') {
	//	changeDir(STAY);
	//}
	//
	
	if (isValidMove() == false) {
		changeDir(STAY);
	}
	if (gravitation()) {
		changeDir(DOWN);
	}
	
	x += dirX;
	y += dirY;
	
	// Better use a function in Board to check if the new position is valid
	// + Better use a constant for the wall character
	//if (pBoard->getChar(newX, newY) == 'W') {
	//	dir = { 0, 0 };
	//}
	//else {
	//	x = newX;
	//	y = newY;
	//}
}