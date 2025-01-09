#pragma once
#include "Board.h"
#include "Mario.h"
//#include "Barrel.h"
#include "MenuGraphics.h"
//#include "Ghost.h"
#include <vector>
#include "Enemy.h"

class Manager
{
	MenuGraphics* menuGraphics;
	Board board;

	int sleepCount = 0; // counter to keep track of the pace of the barrels activation
	int activated_I = 1; // index of the next barrel to be activated
	bool encounters = false;

public:
	Manager(Board b, MenuGraphics* mg) : board(b), menuGraphics(mg) {}

	bool getEncounters() const {
		return encounters;
	}

	// set the encouters value
	void setEncounters(bool value) {
		encounters = value;
	}
	virtual void reset(Board& board) = 0;
	virtual void draw(Mario& mario) = 0;
	virtual void move(Mario& mario) = 0;

	//void smashBarrels(Mario& mario);

	MenuGraphics* getMG() { return menuGraphics; }
	int getSleepCount() { return sleepCount; }
	void setSleepCount(int count) { sleepCount = count; }
	int getActivatedIndex() { return activated_I; }
	void setActivatedIndex(int index) { activated_I = index; }
};

