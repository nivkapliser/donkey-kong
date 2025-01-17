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
	std::vector<Ghost> ghosts;
	int ghostsLocationsMap[26][80] = { 0 }; // for ghost meeting

public:
	GhostManager(Board b, MenuGraphics* mg) : Manager(b, mg) {}

	void reset(Board& board) override;
	void draw(Mario& mario) override;
	void move(Mario& mario) override;

	void smashGhosts(Mario& mario);
	void resetLocationMap();
};