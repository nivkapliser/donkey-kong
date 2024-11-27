#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"

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

	Direction currenDirection = STAY;
	int dirX = 0;
	int dirY = 0;

	bool isJump = false;
	bool isClimbing = false;
	int jumpHeight = 0;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	// add constructors

	void draw() const {
		draw(ch);
	}
	void erase() {
		draw(' ');
	}
	void setBoard(Board& board) {
		pBoard = &board;
	}
	bool isOnLadder() const {
		return pBoard->getChar(x, y) == 'H';
	}
	bool isAtFloor();
	void climbLadder();
	void downLadder();
	bool isLadder();
	void changeDir(Direction dir);
	bool isValidMove();
	bool gravitation();
	void move();
	void keyPressed(char key);


	void jump();


};

