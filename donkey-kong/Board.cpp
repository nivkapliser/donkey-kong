#include "Board.h"
#include <cstring>
#include <iostream>

// Function to reset the board to its original state
// Based on lab code
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);	
	}
}

// Function to print the board
void Board::print() const
{
	menuGraphics->setCurrentColor(menuGraphics->getLightRed());
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}

// Function to check if a move is valid (i.e. not on a forbidden character)
bool Board::isValidMove(int x, int y) const {
	char nextChar = getChar(x, y);
	for (auto ch : FORBIDDEN_CHARS) {
		if (nextChar == ch) {
			return false;
		}
	}
	return true;
}

// Function to check if a given position is a floor
bool Board::isFloor(int x, int y) const { 
	char c = getChar(x, y);
	for (auto ch : FORBIDDEN_CHARS) {
		if (c == ch) { 
			return true;
		}
	}
	
	return false;
}

// Function to check if a given position is a ladder
bool Board::isLadder(int x, int y) const {
	return currentBoard[y][x] == LADDER; 
}

// Function to check if a given position is empty space
bool Board::gravitation(int x, int y) const {
	return getChar(x, y + 1) == EMPTY_SPACE; 
}