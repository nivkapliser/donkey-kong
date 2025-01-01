#include "Hammer.h"
#include "utils.h"
#include "Board.h"


//delete?

// Place hammer randomly on a floor
//void Hammer::placeRandomly(Board& board) {
//    int x, y;
//
//	//std::cout << "started hammer" << std::endl;
//    do {
//        x = rand() % Board::getMaxX(); // need to find out how to use - Board::MAX_X; 
//        //std::cout << "x: " << x << std::endl;
//        y = rand() % Board::getMaxY(); //Board::MAX_Y;
//        //std::cout << "y: " << y << std::endl;
//    } while (!board.isFloor(x, y) || board.getChar(x, y) != ' ');  // Place on floor space
//
//    setX(x);
//	
//    setY(y);
//}