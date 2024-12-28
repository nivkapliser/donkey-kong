#include "Hammer.h"
#include "utils.h"
#include "Board.h"

// Activate hammer for Mario
void Hammer::activate() {
    if (pickedUp) {
        active = true;
		if (sleepCounter >= MAX_SLEEP) {
            active = false;
		}
    }
    sleepCounter += SLEEP_STEP;
}

// Place hammer randomly on a floor
void Hammer::placeRandomly(Board& board) {
    int x, y;
    do {
        x = rand() % 80; // need to find out how to use - Board::MAX_X; 
        y = rand() % 25; //Board::MAX_Y;
    } while (!board.isFloor(x, y) || board.getChar(x, y) != ' ');  // Place on floor space

    setX(x);
    setY(y);
}