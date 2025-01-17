#pragma once
#include "MenuGraphics.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

class Mario; // forward declaration
class Hammer; // forward declaration

class Board
{
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr char EMPTY_SPACE = ' ';
	static constexpr char LADDER = 'H';
	static constexpr char FLOOR[] = { '<', '>', '=' };
	static constexpr char WALL = 'Q';
	static constexpr char PAULINE = '$';
	MenuGraphics* menuGraphics;

	int marioX = -1;
	//int marioY;
	int legendX = -1;
	int legendY = -1;
	int donkeyX = -1;
	int donkeyY = -1;

	std::vector<int> ghostsX;
	std::vector<int> ghostsY;

	char boardFile[MAX_Y][MAX_X + 1];
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator

public:
	//Board() {}
	Board(MenuGraphics* mg) : menuGraphics(mg) { 
		reset();
	}
	void reset();
	void print() const;
	char getChar(int x, int y) const { return currentBoard[y][x]; }
	void setChar(int x, int y, char c) { currentBoard[y][x] = c; }
	void printLegend() const {
		gotoxy(legendX, legendY);
		std::cout << "Lives: " << " | Score: " << std::endl;
		gotoxy(legendX, legendY + 1);
		std::cout << "Hammer: ";
	}
	int getLegendX() const { return legendX; }
	int getLegendY() const { return legendY; }
	
	bool isValidMove(int x, int y) const;
	bool isFloor(int x, int y) const;
	bool isBoarder(int x, int y) const {
		if(getChar(x, y) == WALL || y >= MAX_Y)
			return true;
		return false;
	}
	
	bool isLadder(int x, int y) const { return currentBoard[y][x] == LADDER; }
	bool gravitation(int x, int y, int dirX = 0) const; 
	bool isEmptySpace(int x, int y) const { return getChar(x, y) == EMPTY_SPACE; }
	static int getMaxX() { return MAX_X; }
	static int getMaxY() { return MAX_Y; }
	int getGhostX(int index) { return ghostsX[index]; }
	int getGhostY(int index) { return ghostsY[index]; }
	int getDonkeyKongX() const { return donkeyX; }
	int getDonkeyKongY() const { return donkeyY; }
	size_t getNumGhosts() const { return ghostsX.size(); }
	int readBoard(const std::string& filename, Mario& mario, Hammer& hammer);
	void setStartPositions(std::string line, Mario& mario, Hammer& hammer, int i);
	char getLetter(const char* object);
	int getDimension(char dim) { return tolower(dim) == 'y' ? MAX_Y : MAX_X; }
};


