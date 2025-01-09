#pragma once

/*
* This class is responsible for managing the barrels in the game.
* It is responsible for drawing, moving, and activating the barrels.
* It also checks for collisions between the barrels and mario.
*/

#include "Board.h"
#include "Mario.h"
#include "Barrel.h"
#include "MenuGraphics.h"
#include "Manager.h"

class BarrelManager : public Manager
{
	static constexpr int MAX_BARRELS = 20; // max number of barrels in a game
	static constexpr int BARRELS_PACE = 700; // pace at which barrels are activated

	std::vector<Barrel> barrels;


public:
	BarrelManager(Board b, MenuGraphics* mg) : Manager(b,mg) { barrels.resize(MAX_BARRELS); }

	void reset(Board& board) override;
	void draw(Mario& mario) override; 
	void move(Mario& mario) override;
	void barrelsActivation();
	void smashBarrels(Mario& mario);
};

