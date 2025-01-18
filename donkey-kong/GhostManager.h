#pragma once
#include "Manager.h"
#include "Ghost.h"
#include "MenuGraphics.h"

/*
* This class is responsible for managing the ghosts in the game.
* It is responsible for drawing, moving, and activating the ghosts.
* It also checks for collisions between the ghosts and mario and between two ghosts.
* It is a derived class of Manager.
*/

class Board;
class Mario;

class GhostManager : public Manager
{
	std::vector<Ghost> ghosts;
	int ghostsLocationsMap[26][80] = { 0 }; // for ghost meeting

public:
	GhostManager(Board b, MenuGraphics* mg) : Manager(b, mg) {}

	void reset(Board& board) override;
	void draw(Mario& mario) override;
	void move(Mario& mario) override;

	// GhostManager specific functions
	void smashGhosts(Mario& mario);
	void resetLocationMap();
};