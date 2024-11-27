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
	if (pBoard->getChar(x, y) == 'H') // Ladder in Mario's current place
		return true;
	else if (pBoard->getChar(x, y - 1) == 'H') // ladder in Mario's next place
		return true;
	else if (pBoard->getChar(x, y + 1) == 'H') // to handle last step
		return true;
	return false;
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
	case UP: //can only jump or climb
		if (isLadderUp()) {
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
		if (isLadderDown()) { // can only go down a ladder
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

	if (pBoard->getChar(x + dirX, y + dirY) == 'H') {
		Point ladderPosition = Point(x + dirX, y + dirY, 'H');
		
	}
	
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