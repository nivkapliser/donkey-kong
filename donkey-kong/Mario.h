#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Point.h"

constexpr char FORBIDDEN_CHARS[] = { 'Q', '<', '>', '=' };
constexpr char LADDER = 'H';
constexpr char EMPTY_SPACE = ' ';

class Mario
{
	enum Direction { LEFT, UP, RIGHT, DOWN, STAY }; // should be public?
	static constexpr char keys[] = { 'a', 'w', 'd', 'x', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	static constexpr int START_X = 70;
	static constexpr int START_Y = 23;
	int isJump = false;

	char ch = '@';
	int x = START_X;
	int y = START_Y;
	int lives = 3;

	char lastPoint;

	Direction currenDirection = STAY;
	int dirX = 0;
	int dirY = 0;

	int fallCounter = 0;
	int jumpCounter = 0;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Mario() : x(START_X), y(START_Y), lastPoint(' '), lives(3) {}
	
	void resetMarioPosition() {
		x = START_X;
		y = START_Y;
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}

	int setLives(int l) {
		lives = l;
	}

	int getLives() const {
		return lives;
	}

	void downLives() {
		lives--;
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
//
//void Mario::jump() {
//
//	isJump = true; // to avoid gravitation
//	dirY = -1;
//	for (int i = 0; i < 2; i++) {
//		Sleep(100);
//		dirY = 0;
//		isJump = false;
//
//	}
