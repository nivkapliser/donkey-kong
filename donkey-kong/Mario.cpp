#include "Mario.h"

// Function to change the direction of Mario
// based on code from the lab
void Mario::changeDir(Direction dir) {
    switch (dir) {
    case LEFT:
        dirY = 0;
        dirX = -1;
        break;
    case UP:
        dirY = -1;
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

// Function to handle key press
// based on code from the lab
void Mario::keyPressed(char key) {
    for (size_t i = 0; i < numKeys; i++) {
        if (std::tolower(key) == keys[i]) {
            changeDir(static_cast<Direction>(i));
            break;
        }
    }
}

// Function to handle marios movement logic
// built base on the lab code
void Mario::move() {

    // Ladder climbing logic
	if (pBoard->isLadder(x, y) || pBoard->isLadder(x, y + 1)) { 
        if (dirY == -1) {
            // Climbing up
            if (pBoard->isLadder(x, y - 1)) {
                y--;
                return;
            }
			else if (pBoard->isFloor(x, y - 1)) {
            // Climbing last level
                y -= 2;
                changeDir(STAY);
                return;
            }
        }
        else if (dirY == 1 && pBoard->isLadder(x, y + 2)) {
            // Deccending ladder
            y++;
            return;
        }
    }

    int newX = x + dirX;
    int newY = y + dirY;
    bool gravity = false;
    
    // first step in climbing down ladder
    if (dirX == 0 && dirY == 1 &&
        pBoard->isLadder(x, y + 2) &&
        pBoard->isFloor(x, y + 1)) {
        y += 2;
    }

	// stop if next step is not valid
    else if (!pBoard->isValidMove(newX, newY)) {
        changeDir(STAY);
    }

	// gravity logic
    else if (pBoard->gravitation(x, y) && !isJump && pBoard->isValidMove(newX, y+1)) { 
        gravity = true;
        y++;
        x += dirX;
    }

	// jump logic
    else if (isJump != 0)
        jump(); 
    
    // to start the jump
    else if (dirY == -1 && pBoard->isEmptySpace(x, y - 2)&& !isJump) {
        x = newX; 
        y = newY; 
        isJump = 1;
    }

	// to handle the case when mario is on the ladder and the next step is floor
    else if (!pBoard->isValidMove(newX, newY) && pBoard->isLadder(x, y) && !isJump) {
        y -= 2;
    }

    else {
        if (!isJump)
        {
            x = newX;
            y = newY;
        }

    }

    fallCounter = gravity ? ++fallCounter : 0; 
}

// Function to handle marios jump logic
void Mario::jump()
{
    if (isJump < JUMP_HEIGHT)  
    {
        x += dirX;
        y += dirY;
        isJump++;
    }
    else
    {
        x += dirX;
        dirY = 0;
        isJump = 0;
    }
}

// Function to draw mario explosion
void Mario::explode()
{
    erase();
    gotoxy(x - 2, y - 2);
    std::cout << "OUCH!";
    gotoxy(x - 2, y);
    std::cout << "_\\|/_";
    Sleep(700); // longer Sleep time for visual effect
}




