#include "Hammer.h"
#include "utils.h"
#include "Board.h"


//delete?

// Place hammer randomly on a floor
void Hammer::placeRandomly(Board& board) {
    int x, y;
    do {
        x = rand() % Board::getMaxX(); // need to find out how to use - Board::MAX_X; 
        y = rand() % Board::getMaxY(); //Board::MAX_Y;
    } while (!board.isFloor(x, y) || board.getChar(x, y) != ' ');  // Place on floor space

    setX(x);
    setY(y);
}