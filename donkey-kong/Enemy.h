#pragma once
#include "Board.h"
#include "Mario.h"
#include "utils.h"

/*
* This class represents an entity in the game. 
* every specific entity will inherit from this class.
*/

class Enemy
{
	static constexpr char EMPTY_SPACE = ' ';

	char ch;
	int x;
	int y;

	char floor[5] = "<>=Q";
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]); // to get the size of the floor array

	enum Direction { LEFT, RIGHT, SAME, STOP }; // to set the direction of the barrel
	int dirX = 0;
	int dirY = 0;

	bool active; // for the barrelsManager to check if the barrel is active
	char lastPoint; // to save the last point char for latter printing

	bool encountered = false;

	Board* pBoard = nullptr;


	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

protected: // need to decide
	

public:
	Enemy() {}
	Enemy(int start_x, int start_y, char _c, bool _active) : x(start_x), y(start_y), ch(_c), active(_active) {}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}

	void setX(int _x) {
		x = _x;
	}

	void setY(int _y) {
		y = _y;
	}

	void setChar(char _c) {
		ch = _c;
	}

	void draw() const {
		draw(ch);
	}
	void erase() {
		setLastPoint();
		draw(lastPoint);
	}

	int getDirX() const {
		return dirX;
	}
	int getDirY() const {
		return dirY;
	}

	void setDirX(int _dirX) {
		dirX = _dirX;
	}

	void setDirY(int _dirY) {
		dirY = _dirY;
	}

	// Function to set the last point of the barrel
	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	// Function to set the board for the barrel
	void setBoard(Board& board) {
		pBoard = &board;
	}

	// Function to check if the barrel is active
	bool checkActivationStatus() const {
		return active;
	}

	bool isActive() const {
		return active;
	}

	Board& getBoard() const {
		return *pBoard;
	}

	void changeDir(Direction dir);
	void move() {
		x += dirX;
		y += dirY;
	}
	void resetLocation(int start_x, int start_y) { x = start_x; y = start_y; }
	void activation(bool b) { active = b; }; //need to be Enemy activator
	bool checkEncounters(Mario& mario);
	int getDirectionRandomly() const;

};

