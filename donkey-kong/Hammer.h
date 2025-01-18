#pragma once
#include "Board.h"

/*
* This class represents the hammer that mario can pick up and smash barrels with.
* The hammer is represented by the character 'p' and is drawn on the board.
*/

class Hammer
{
	static constexpr char HAMMER_CHAR = 'p';

	// hammer settings
	char c = HAMMER_CHAR;
	int x;
	int y;
	int startX;
	int startY;

	// state of the hammer
	char lastPoint;
	bool active = true;		// if is active mario can pick it up and smash barrels
	bool collected = false;
	int sleepCounter = 0;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Hammer() {}

	// some getters and setters
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	void setStartX(int x) { startX = x; }
	void setStartY(int y) { startY = y; }
	void setBoard(Board& board) { pBoard = &board; }
	void setLastPoint() { lastPoint = pBoard->getChar(x, y); }

	void resetPosition() {
		x = startX;
		y = startY;
	}

	// drawing and erasing the hammer
	void draw() const {
		if (!collected)
			draw(c);	
	}
	void erase() {
		if (collected) {
			setLastPoint();
			draw(lastPoint);
		}
	}

	// state update functions
	void setCollected(bool b) { collected = b; }
	bool isCollected() const { return collected; }
};

