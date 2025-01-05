#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"

class Ghost
{
	//static constexpr int START_X = 17; // for barrels that start from the left
	//static constexpr int START_Y = 7;


	char ch = 'x';
	int x;
	int y;

	char floor[5] = "<>=Q"; // to set the direction of the barrel
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]); // to get the size of the floor array

	enum Direction { LEFT, RIGHT, SAME, STOP }; // to set the direction of the barrel
	int dirX = -1;
	int dirY = 0;

	char lastPoint; // to save the last point char for latter printing

	bool ghostsMeeting = false;
	bool encountered = false; //MAYBE WE CAN DELETE THIS 
	bool active = true;


	Board* pBoard = nullptr;


	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

	// should be more general for multiple boards



public:
	Ghost() {}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	int getDirX() const{
		return dirX;
	}
	int getDirY() const {
		return dirY;
	}


	void draw() const {
		draw(ch);
	}
	void erase() {
		setLastPoint();
		draw(lastPoint);
	}

	// Function to set the last point of the barrel
	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	// Function to set the board for the barrel
	void setBoard(Board& board) {
		pBoard = &board;
	}

	void setActive(bool b) {
		active = b;
	}

	bool isActive() const {
		return active;
	}

	void switchGhostsMeeting();


	void changeDir(Direction dir);
	void move();
	void floorDirSync();
	bool checkEncounters(Mario& mario); //MAYBE WE CAN DELETE THIS
	int getDirectionRandomly() const;
	bool isFloorEnd() const;
	void resetLocation (int start_x, int start_y) { x = start_x; y = start_y; }
};
