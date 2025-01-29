//#pragma once
//
//#include "Barrel.h"
//#include "MenuGraphics.h"
//#include "Manager.h"
//
///*
//* This class is responsible for managing the barrels in the game.
//* It is responsible for drawing, moving, and activating the barrels.
//* It also checks for collisions between the barrels and mario.
//* It is a derived class of Manager.
//*/
//
//class Mario;
//class Board;
//
//class BarrelManager : public Manager
//{
//	static constexpr int MAX_BARRELS = 20;      // max number of barrels in a game
//	static constexpr int BARRELS_PACE = 700;    // pace at which barrels are activated
//
//	std::vector<Barrel> barrels;
//
//	int sleepCount = 0;			// counter to keep track of the pace of the activation
//	int activated_I = 1;		// index of the next barrel to be activated
//	
//public:
//	BarrelManager(Board b, MenuGraphics* mg) : Manager(b,mg) { barrels.resize(MAX_BARRELS); }
//
//	void reset(Board& board) override;
//	void draw(Mario& mario) override; 
//	void move(Mario& mario) override;
//
//	// BarrelManager specific functions
//	void barrelsActivation();
//	void smashBarrels(Mario& mario);
//};
//
