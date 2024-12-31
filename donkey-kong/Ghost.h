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
	int y = getRandomYpos();

	char floor[5] = "<>=Q"; // to set the direction of the barrel
	static constexpr size_t floorTypes = sizeof(floor) / sizeof(floor[0]); // to get the size of the floor array

	enum Direction { LEFT, RIGHT, SAME, STOP }; // to set the direction of the barrel
	int dirX = -1;
	int dirY = 0;

	bool isActive; // for the barrelsManager to check if the barrel is active
	char lastPoint; // to save the last point char for latter printing

	bool encountered = false; //MAYBE WE CAN DELETE THIS 

	Board* pBoard = nullptr;


	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

	const int getRandomYpos()
	{
		if (randomZeroOrOne() == 0)
			return 11;
		else
			return 16;
	}


	const int getRandomXpos()
	{
		if (y == 11)
		{
			if (randomZeroOrOne() == 0)
				return (abs(rand() % 100) / 5) + 3;
			else
				return (abs(rand() % 100) / 5) + 53;
		}
		else
		{
			if (randomZeroOrOne() == 0)
				return (abs(rand() % 100) / 5) + 3;
			else
				return (abs(rand() % 100) / 6) + 50;
		}

	}



public:
	Ghost() : y(getRandomYpos()), x(getRandomXpos()) { isActive = false; }

	static bool ghostsLocationsMap[25][80]; //talk with niv about the static constants of board


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
		return isActive;
	}


	void changeDir(Direction dir);
	void move();
	void floorDirSync();
	void ghostActivation(); //need to be Enemy activator
	bool checkEncounters(Mario& mario); //MAYBE WE CAN DELETE THIS
	int getDirectionRandomly() const;
	bool isFloorEnd() const;
};
