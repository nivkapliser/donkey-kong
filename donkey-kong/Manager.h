#pragma once
#include "Enemy.h"
#include "Board.h"
#include "Mario.h"
#include "MenuGraphics.h"
#include <vector>

/*
* Manager class is an abstract class that is responsible for managing the game enemies.
* The specific managers for each enemy inherit from this class.
*/

class Manager
{
	MenuGraphics* menuGraphics;
	Board board;

	bool encounters = false;

public:
	Manager(Board b, MenuGraphics* mg) : board(b), menuGraphics(mg) {}
	virtual ~Manager() = default;

	// Getters and Setters
	MenuGraphics* getMG() { return menuGraphics; }
	bool getEncounters() const { return encounters; }
	void setEncounters(bool value) { encounters = value; }

	// move, draw, and reset functions are pure virtual functions
	virtual void reset(Board& board) = 0;
	virtual void draw(Mario& mario) = 0;
	virtual void move(Mario& mario) = 0;
};

