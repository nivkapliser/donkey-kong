#pragma once
#include "MenuGraphics.h"
#include <iostream>
#include <cstring>


class Board
{
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr char EMPTY_SPACE = ' ';
	static constexpr char LADDER = 'H';
	static constexpr char FORBIDDEN_CHARS[] = { 'Q', '<', '>', '=' };
	static constexpr char PAULINE = '$';
	MenuGraphics* menuGraphics;

	const char* originalBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  " Remaining Lives:                                                               ", // 0
		  "                                                                                ", // 1
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 2
		  "Q                                    $                                         Q", // 3
		  "Q                          =====================                               Q", // 4
		  "Q                          H                   H                               Q", // 5
		  "Q                          H                   H                               Q", // 6
		  "Q                          H         &         H                               Q", // 7
		  "Q        <<<<<<<<<<<<<<<<<<<<<<<<<<<<=>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         Q", // 8
		  "Q        H                                                           H         Q", // 9
		  "Q        H                                                           H         Q", // 10
		  "Q        H                                                           H         Q", // 11
		  "Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>                 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 12
		  "Q     H                                       H                                Q", // 13
		  "Q     H                                       H                                Q", // 14
		  "Q     H                                       H                                Q", // 15			
		  "Q     H                                       H                                Q", // 16
		  "Q>>>>>>>>>>>>>>>>>>>>>                        <<<<<<<<<<<<<<<<<<<<<<<<<        Q", // 17
		  "Q                    H                                                H        Q", // 18
		  "Q                    H                                                H        Q", // 19
		  "Q                    H                                                H        Q", // 20
		  "Q                    H                                                H        Q", // 21
		  "Q                    H                                                H        Q", // 22
		  "Q                    H                                                H        Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator

public:
	Board(MenuGraphics* mg) : menuGraphics(mg) { reset(); }
	void reset();
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}

	bool isValidMove(int x, int y) const;
	bool isFloor(int x, int y) const;
	bool isLadder(int x, int y) const;
	bool gravitation(int x, int y) const; 
	bool isEmptySpace(int x, int y) const {
		return getChar(x, y) == EMPTY_SPACE;
	}
};


