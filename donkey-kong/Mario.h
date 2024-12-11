#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Point.h"
#include "Barrel.h"

class Mario
{
	enum Direction { LEFT, UP, RIGHT, DOWN, STAY };
	static constexpr int JUMP_HEIGHT = 2;
	static constexpr char keys[] = { 'a', 'w', 'd', 'x', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	static constexpr int START_X = 70;
	static constexpr int START_Y = 23;
	static constexpr int MAX_LIVES = 3;

	//Point mario = Point(START_X, START_Y);
	
	char ch = '@';
	int x = START_X;
	int y = START_Y;
	int lives;

	Direction currentDirection = STAY;
	int dirX = 0;
	int dirY = 0;

	char lastPoint; // point
	int isJump = false; //???
	int fallCounter = 0;
	int jumpCounter = 0;
	//bool metBarrel = false;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Mario() : x(START_X), y(START_Y), lastPoint(' '), lives(3) {}
	//~Mario() { delete pBoard; }

	void resetMarioPosition() {
		x = START_X;
		y = START_Y;
		dirX = 0;
		dirY = 0;
	}
	void resetLives() {
		setLives(MAX_LIVES);
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}

	void setLives(int l) {
		lives = l;
	}

	int getLives() const {
		return lives;
	}

	int getFallCounter() const {
		return fallCounter;
	}

	void downLives() {
		lives--;
		eraseLife();
		drawLife();
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

	void eraseLife() {
		gotoxy(18, 0);
		std::cout << ' ';
	}

	void drawLife() {
		gotoxy(18, 0);
		std::cout << lives;
	}

	void changeDir(Direction dir);
	void move();
	void keyPressed(char key);
	void jump();
	bool metPauline() const;
	bool isOnFloor() const;
	//bool checkEncounters(Barrel& barrel); // change to point?
};
