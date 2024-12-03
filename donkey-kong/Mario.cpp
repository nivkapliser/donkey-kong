#include "Mario.h"


/*\
TODO: 
	1. save constants with constexpr
	2. think about implement the climbing/down ladder inside "move" (checking if there is ladder and canging dirY. Barrels can't move at the same time as Mario) 
	3. implement the jump inside move (same reasons as climb)
	4.
*/





/*This function checks if there is ladder above Mario*/
bool Mario::isLadderUp() {
	if (pBoard->getChar(x, y - 1) == 'H') // ladder in Mario's next place
		return true;
	return false;
}

bool Mario::isLadder() {
	return pBoard->getChar(x, y) == 'H';
}

bool Mario::isFloorUp() {
	for (int i = 0; i < 5; i++) {
		if (pBoard->getChar(x, y - 1) == dontTouch[i]) {
			return true;
		}
	}
}

/*This function checks if there is ladder below Mario*/
bool Mario::isLadderDown() {
	if (pBoard->getChar(x, y + 2) == 'H' || pBoard->getChar(x, y + 1) == 'H')
		return true;
	return false;
}

/*This function implement the ladder climbing logic*/
void Mario::climbLadder() { 
	dirY = -1;
	dirX = 0;
	while (isLadderUp()) { 
		erase();
		y += dirY;
		draw();
		Sleep(175);
	}	
	changeDir(STAY); // to stop moving at the end of the climb
}

/*This function implement the getting down the ladder logic*/
void Mario::downLadder() {
	dirY = 1;
	dirX = 0;
	while (isLadderDown())
	{
		erase();
		y += dirY;
		draw();
		Sleep(175);
	}
	changeDir(STAY);
}

/*This function implement gravitation when Mario reach the end of a surface*/
bool Mario::gravitation() {
	if (pBoard->getChar(x, y + 1) == ' ' && isJump == false) { // save constant
		return true;
	}
	return false;
}

/*This function checks if Mario next move is a valid move (not "Q,<,>,=")*/
bool Mario::isValidMove() {
	for (int i = 0; i < 5; i++) { // change to the one like python
		if (pBoard->getChar(x + dirX, y + dirY) == dontTouch[i]) {
			return false;
		}
	}
	return true;
}

/*This function implement the jump logic*/
void Mario::jump() {

	isJump = true; // to avoid gravitation

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

/*This function sets Mario direction*/
void Mario::changeDir(Direction dir) {
	switch (dir) {
	case LEFT:
		dirY = 0;
		dirX = -1;
		break;
	case UP: 
		dirY = -1;
		dirX = 0;
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

/*This function handles keyboard press and change Mario's direction based on the key pressed*/
void Mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			changeDir((Direction)i);
		}
	}
}

/*This function handles Morio movement logic*/
void Mario::move() {
	int newX = x + dirX;
	int newY = y + dirY;



	if (dirX == 0 && dirY == -1 && isLadder()) {  // climbing ladder
		if (isFloorUp() && !isLadderUp()) {  // last climbing ladder step
			y -= 2;
			changeDir(STAY);
		}
		else {
			y--;
		}
	}
	else if (dirX == 0 && dirY == 1 && isLadder()) { // descending ladder
		if (isLadderDown()) {  // last descending ladder step
			y += 2;
			changeDir(STAY);
		}
		else {
			y++;
		}
	}
	else if (!isValidMove()) {
		changeDir(STAY);
	}
	else if (gravitation()) {
		changeDir(DOWN);
		y++;
	}
	else {
		x = newX;
		y = newY;
	}
}
