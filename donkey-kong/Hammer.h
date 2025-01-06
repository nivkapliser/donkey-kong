#pragma once

#include "Board.h"

class Hammer
{
	static constexpr char HAMMER_CHAR = 'p';
	static constexpr int MAX_SLEEP = 500;
	static constexpr int SLEEP_STEP = 50;

	char c = HAMMER_CHAR;
	int x = 1;
	int y = 1;
	char lastPoint;

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

	int getX() const {
		return x;
	}

	int getY() const {
		return y;
	}

	void setX(int newX) {
		x = newX;
	}

	void setY(int newY) {
		y = newY;
	}

	void draw() const {
		if (!collected)
			draw(c);	
	}

	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	void erase() {
		if (collected) {
			setLastPoint();
			draw(lastPoint);
		}
	}
	
	void setCollected(bool b) {
		collected = b;
	}

	bool isCollected() const {
		return collected;
	}

	void placeRandomly(Board& board);
};

