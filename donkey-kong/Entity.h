#pragma once
#include "Board.h"

/*
* This class represents an entity in the game. 
* every specific entity will inherit from this class.
*/

class Entity
{
	char ch;
	int x;
	int y;

	// add direction enum?
	int dirX;
	int dirY;

	char lastPoint; // for printing after player passes through

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	// getX
	int getX() const {
		return x;
	}

	// getY
	int getY() const {
		return y;
	}

	// setX
	void setX(int newX) {
		x = newX;
	}

	// setY
	void setY(int newY) {
		y = newY;
	}

	// getChar
	char getChar() const {
		return ch;
	}

	// draw
	void draw() const { // add colors
		draw(ch);
	}


	// setLastPoint
	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	// erase
	void erase() {
		setLastPoint();
		draw(lastPoint);
	}

	// setBoard
	void setBoard(Board& board) {
		pBoard = &board;
	}
	
	// move?
	// changeDir

};

