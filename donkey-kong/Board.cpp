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

bool Board::isValidMove(int x, int y) const {
	char nextChar = getChar(x, y);
	for (auto ch : FORBIDDEN_CHARS) {
		if (nextChar == ch) {
			return false;
		}
	}
	return true;
}

bool Board::isFloor(int x, int y) const { 
	char c = getChar(x, y);
	for (auto ch : FORBIDDEN_CHARS) {
		if (c == ch) { 
			return true;
		}
	}
	
	return false;
}

bool Board::isLadder(int x, int y) const {
	return currentBoard[y][x] == LADDER; // change to saved word LADDER
}

bool Board::gravitation(int x, int y) const {
	return getChar(x, y + 1) == EMPTY_SPACE; // change to saved word EMPTY_SPACE
}