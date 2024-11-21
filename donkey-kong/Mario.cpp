#include "Mario.h"

void Mario::isValidMove() {
	for (int i = 0; i < 5; i++) {
		if (pBoard->getChar(x, y - 1) == dontTouch[i]) {

		}
	}
}

void Mario::jump() {

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
	

}

void Mario::changeDir(Direction dir) {
	switch (dir) {
	case LEFT:
		dirY = 0;
		dirX = -1;
		break;
	case UP:
		jump();
		//dirY = -1;
		//dirX = 0;
		break;
	case RIGHT:
		dirY = 0;
		dirX = 1;
		break;
	case DOWN:
		dirY = 1;
		dirX = 0;
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

	if (pBoard->getChar(x + dirX, y + dirY) == 'Q') {
		changeDir(STAY);
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