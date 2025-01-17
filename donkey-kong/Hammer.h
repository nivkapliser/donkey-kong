#pragma once

#include "Board.h"

class Hammer
{
	static constexpr char HAMMER_CHAR = 'p';

	char c = HAMMER_CHAR;
	int x;
	int y;
	char lastPoint;
	int startX;
	int startY;

	bool active = true; // if is active mario can pick it up and smash barrels
	bool collected = false;
	int sleepCounter = 0;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Hammer() {}

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	void setStartX(int x) { startX = x; }
	void setStartY(int y) { startY = y; }

	void resetPosition() {
		x = startX;
		y = startY;
	}

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

	void setBoard(Board& board) { pBoard = &board; }
	void setLastPoint() { lastPoint = pBoard->getChar(x, y); }
	void setCollected(bool b) { collected = b; }
	bool isCollected() const { return collected; }
};

