#include "Hammer.h"
#include "utils.h"
#include "Board.h"



// Place hammer randomly on a floor
void Hammer::placeRandomly(Board& board) {
    int x, y;

	srand(time(0));
    do {
        x = rand() % Board::getMaxX();  
        y = rand() % Board::getMaxY(); 
    } while (!board.isFloor(x, y + 1) || board.getChar(x, y) != ' ');  // Place on floor space

    setX(x);
    setY(y);
}