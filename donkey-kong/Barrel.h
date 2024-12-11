#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Mario.h"

class Mario;

class Barrel
{
	static constexpr int START_X_R = 38;
	static constexpr int START_X_L = 36;
	static constexpr int START_Y = 7;
	static constexpr int FALL_LIMIT = 8;
	static constexpr int EXPLODE_ZONE = 2;


	char ch = 'O';
	int x;
	int y;
	char floor[5] = "<>=Q"; // FORBIDDEN_CHARS??
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]);
	enum Direction { LEFT, RIGHT, SAME, BOTTOM };
	int dirX = 0;
	int dirY = 0;
	bool isActive;
	char lastPoint;
	int linesFallen = 0;
	bool encountered = false;
	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}
	bool isFalling = false;
	bool isExploding = false;

public:
	Barrel() : x((getDirectionRandomly() == 1) ? START_X_R:START_X_L), y(START_Y) { isActive = false;}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void draw() const {
		draw(ch);
	}
	void erase() {
		setLastPoint();
		draw(lastPoint);
	}
	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	void changeDir(Direction dir);
	void move();
	void setBoard(Board& board) {
		pBoard = &board;
	}
	void floorDirSync();
	void explode();
	bool barrelFallManager();

	bool checkActivationStatus() const {
		return isActive;
	}

	void barrelActivation();
	void eraseBoom();
	bool fallingStatus() const {
		return isFalling;
	}
	bool checkEncounters(Mario& mario);
	int getDirectionRandomly();
};


