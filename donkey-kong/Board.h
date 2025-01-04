#pragma once
#include "MenuGraphics.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>



class Board
{
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr char EMPTY_SPACE = ' ';
	static constexpr char LADDER = 'H';
	static constexpr char FORBIDDEN_CHARS[] = { '<', '>', '=' }; // change to floor
	static constexpr char WALL = 'Q';
	static constexpr char PAULINE = '$';
	MenuGraphics* menuGraphics;

	int marioX;
	int marioY;
	int paulineX;
	int paulineY;
	int legendX;
	int legendY;
	int donkeyX;
	int donkeyY;
	int ghostsX[7];
	int ghostsY[7];

	char boardFile[MAX_Y][MAX_X + 1];
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator

public:
	//Board() {}
	Board(MenuGraphics* mg) : menuGraphics(mg) { 
		readBoard();
		reset();
	}
	void reset();
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
	void setChar(int x, int y, char c) {
		currentBoard[y][x] = c;
	}
	void printLegend() const {
		gotoxy(legendX, legendY);
		std::cout << "Lives: " << " | Score: " << std::endl;
		std::cout << " Hammer: ";
	}
	int getLegendX() const {
		return legendX;
	}
	int getLegendY() const {
		return legendY;
	}
	int readBoard();
	bool isValidMove(int x, int y) const;
	bool isFloor(int x, int y) const;
	bool isLadder(int x, int y) const;
	bool gravitation(int x, int y) const; 
	bool isEmptySpace(int x, int y) const {
		return getChar(x, y) == EMPTY_SPACE;
	}
	static int getMaxX() {
		return MAX_X;
	}
	static int getMaxY() {
		return MAX_Y;
	}

	int getGhostX(int index) {
		return ghostsX[index];
	}
	int getGhostY(int index) {
		return ghostsY[index];
	}

};


