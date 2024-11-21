#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"


class Mario
{

	static constexpr char keys[] = { 'a', 'w', 'd', 'x', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	static constexpr int START_X = 70;
	static constexpr int START_Y = 23;
	char ch = '@';
	int x = START_X;
	int y = START_Y;
	enum Direction { LEFT, UP, RIGHT, DOWN, STAY }; // inner private struct
	int dirX = 0;
	int dirY = 0;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	void draw() const {
		draw(ch);
	}
	void erase() {
		draw(' ');
	}
	
	void changeDir(Direction dir);
	void isValidMove();
	void move();
	void keyPressed(char key);
	void setBoard(Board& board) {
		pBoard = &board;
	}

	void jump();


};

