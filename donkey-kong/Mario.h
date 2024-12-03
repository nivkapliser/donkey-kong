#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Point.h"

enum Direction { LEFT, UP, RIGHT, DOWN, STAY }; // should be public?

class Mario
{

	static constexpr char keys[] = { 'a', 'w', 'd', 'x', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	static constexpr int START_X = 70;
	static constexpr int START_Y = 23;

	char ch = '@';
	int x = START_X;
	int y = START_Y;

	char lastPoint;

	Direction currenDirection = STAY;
	int dirX = 0;
	int dirY = 0;

	int fallCounter = 0;
	bool isJump = false;
	bool isClimbing = false;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Mario() : x(START_X), y(START_Y), lastPoint(' ') {}
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
	void setBoard(Board& board) {
		pBoard = &board;
	}

	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	bool isFloor(char ch) const;
	bool isLadder() const;
	bool isLadderUp() const; // delete
	bool isLadderDown() const; // delete
	void changeDir(Direction dir);
	bool isValidMove() const;
	bool gravitation() const; // move to game?
	void move();
	void keyPressed(char key);
};

