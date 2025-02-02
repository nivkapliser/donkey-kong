#pragma once
#include "MenuGraphics.h"
#include <fstream>
#include <string>
#include <vector>

class Mario;  
class Hammer; 

/*
* This class is responsible for the game board.
* It handles reading, storing, and printing the game board.
* It contains methods to check the validity of a moves on board (floor, ladder, empty space, etc.).
* It also contains methods to get the start positions of the entities and ghosts.
*/

class Board
{	
	// for game board settings
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr char EMPTY_SPACE = ' ';
	static constexpr char LADDER = 'H';
	static constexpr char FLOOR[] = { '<', '>', '=' };
	static constexpr char WALL = 'Q';
	static constexpr char PAULINE = '$';
	enum Mandatory { MARIO, DONKEY, LEGEND, GHOST, SPAC_GHOST, HAMMER, PAULI, LADD, FL0, FL1, FL2 }; // enum for mandatory chars in the board
	
	// to get the start position of the entities
	int legendX = -1;
	int legendY = -1;
	int donkeyX = -1;
	int donkeyY = -1;
	int set_table[11] = {}; //table which checks every mandatory char has been set

	// to get the start position of the ghosts
	std::vector<int> ghostsX;
	std::vector<int> ghostsY;
	std::vector<int> spaGhostsX;
	std::vector<int> spaGhostsY;

	// to store the board
	char boardFile[MAX_Y][MAX_X + 1];
	char currentBoard[MAX_Y][MAX_X + 1];
	std::string curr_board_name;
	MenuGraphics* menuGraphics;
	bool silent = false;
	bool loadMode = false; 

public:
	Board(MenuGraphics* mg) : menuGraphics(mg) { 
		reset();
	}

	// some getters and setters
	char getChar(int x, int y) const { return currentBoard[y][x]; }
	void setChar(int x, int y, char c) { currentBoard[y][x] = c; }
	int getLegendX() const { return legendX; }
	int getLegendY() const { return legendY; }
	static int getMaxX() { return MAX_X; }
	static int getMaxY() { return MAX_Y; }
	int getGhostX(int index) const { return ghostsX[index]; }
	int getGhostY(int index) const { return ghostsY[index]; }
	int getSpacialGhostX(int index) const { return spaGhostsX[index]; }
	int getSpacialGhostY(int index) const { return spaGhostsY[index]; }
	int getDonkeyKongX() const { return donkeyX; }
	int getDonkeyKongY() const { return donkeyY; }
	size_t getNumGhosts() const { return ghostsX.size(); }
	size_t getNumSpacialGhosts() const { return spaGhostsX.size(); }
	char getLetter(const char* object);
	int getDimension(char dim) { return tolower(dim) == 'y' ? MAX_Y : MAX_X; }
	void setSilent(bool s) { silent = s; }
	bool getSilent() const { return silent; }
	void setLoadMode(bool l) { loadMode = l; }
	bool getLoadMode() const { return loadMode; }

	// reading, printing, and setting the board
	void reset();
	void print() const;
	int readBoard(const std::string& filename, Mario& mario, Hammer& hammer);
	int setStartPositions(std::string line, Mario& mario, Hammer& hammer, int i);
	void printLegend() const;
	
	// moves checking
	bool isValidMove(int x, int y) const;
	bool isFloor(int x, int y) const;
	bool isLadder(int x, int y) const { return currentBoard[y][x] == LADDER; }
	bool gravitation(int x, int y, int dirX = 0) const; 
	bool isEmptySpace(int x, int y) const { return getChar(x, y) == EMPTY_SPACE; }
	bool isBoarder(int x, int y) const;
	std::string& getBoardName() { return curr_board_name; }

};


