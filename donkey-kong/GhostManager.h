#pragma once
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"
#include "MenuGraphics.h"
#include "Ghost.h"
#include <vector>
#include "Manager.h"


class GhostManager : public Manager
{
	static constexpr int MAX_GHOSTS = 7; // max number of ghosts in a game

	std::vector<Ghost> ghosts;

	int ghostsLocationsMap[25][80]; // what is this???

public:
	GhostManager(Board b, MenuGraphics* mg) : Manager(b, mg) {}

	//void initGhosts(Board& board);
	void reset(Board& board) override;
	void draw(Mario& mario) override;
	void move(Mario& mario) override;
	void smashGhosts(Mario& mario);
};