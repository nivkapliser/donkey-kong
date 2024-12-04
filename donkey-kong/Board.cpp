#include "Board.h"
#include <cstring>
#include <iostream>

void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

void Board::print() const
{
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}

bool Board::isFloor(char ch) const { // change to coord?
	for (int i = 0; i < 5; ++i) {
		if (ch == dontTouch[i]) { // change to forbiden after deleting from mario
			return true;
		}
	}
	
	return false;
}

bool Board::isLadder(int x, int y) const {
	return currentBoard[y][x] == 'H'; // change to saved word LADDER
}

bool Board::gravitation(int x, int y) const {
	return getChar(x, y + 1) == ' '; // change to saved word EMPTY_SPACE
}