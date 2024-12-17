#pragma once

/*
* This class represents a barrel in the game. the barrel can move in 4 directions: left, right, bottom and same.
* The barrel can fall down from the floor and 'explode' when it encounters with mario.
* If the barrel falls down 8 lines, it will be 'explode' and deactivated.
*/

#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Mario.h"

class Barrel
{
	static constexpr int START_X_R = 38; // for barrels that start from the right
	static constexpr int START_X_L = 36; // for barrels that start from the left
	static constexpr int START_Y = 7; 
	static constexpr int FALL_LIMIT = 8; // how many lines can a barrel fall
	static constexpr int EXPLODE_ZONE = 2; // for encountering with mario

	
	char ch = 'O';
	int x;
	int y;

	char floor[5] = "<>=Q"; // to set the direction of the barrel
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]); // to get the size of the floor array

	enum Direction { LEFT, RIGHT, SAME, STOP}; // to set the direction of the barrel
	int dirX = 0; 
	int dirY = 0;

	bool isActive; // for the barrelsManager to check if the barrel is active
	char lastPoint; 

	int linesFallen = 0;
	bool encountered = false;
	bool isFalling = false;
	bool isExploding = false;

	Board* pBoard = nullptr;
	

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}
	

public:
	Barrel() : x((getDirectionRandomly() == 1) ? START_X_R:START_X_L), y(START_Y) { isActive = false;}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void draw() const {
		draw(ch);
	}
	void erase() {
		setLastPoint();
		draw(lastPoint);
	}
	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}
	void setBoard(Board& board) {
		pBoard = &board;
	}
	bool checkActivationStatus() const {
		return isActive;
	}
	bool fallingStatus() const {
		return isFalling;
	}

	void changeDir(Direction dir);
	void move();
	void floorDirSync();
	void explode();
	bool barrelFallManager();
	void barrelActivation();
	void eraseBoom() const;
	bool checkEncounters(Mario& mario);
	int getDirectionRandomly() const;
};


