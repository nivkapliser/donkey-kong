#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Mario.h"

constexpr int MAX_BARRELS = 10;
constexpr int BARRELS_PACE = 1500;
constexpr int FALL_LIMIT = 8;
constexpr int EXPLODE_ZONE = 2;


class Barrel
{
	static constexpr int START_X = 11;
	static constexpr int START_Y = 7;

	char ch = 'O';
	int x;
	int y;
	char floor[5] = "<>=Q";
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]);
	enum Direction { LEFT, RIGHT, SAME, BOTTOM };
	int dirX = 0;
	int dirY = 0;
	bool isActive;
	char lastPoint;
	int linesFallen = 0;
	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}
	bool isFalling = false;
	bool isExploding = false;
public:
	Barrel() : x(START_X), y(START_Y) { isActive = false; }
	int getX() {
		return x;
	}
	int getY() {
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
	bool gravitation();
	void move();
	void setBoard(Board& board) {
		pBoard = &board;
	}

	bool isValidMove();
	void floorDirSync();
	void explode();
	bool barrelFallManager();

	bool checkActivationStatus() {
		return isActive;
	}

	void barrelActivation();
	void eraseBoom();
	bool fallingStatus(){
		return isFalling;
	}
	bool checkEncounters(Mario& mario);
};


