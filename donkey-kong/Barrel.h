#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"

class Barrel
{
	static constexpr int START_X = 11;
	static constexpr int START_Y = 7;
	char ch = 'O';
	int x = START_X;
	int y = START_Y;
	char floor[4] = "<>=";
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]);
	enum Direction { LEFT, RIGHT, SAME };
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
	bool gravitation();
	void move();
	void setBoard(Board& board) {
		pBoard = &board;
	}

	bool isValidMove();
	void floorDirSync();

};

