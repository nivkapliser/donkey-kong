#pragma once
#include "Enemy.h"
#include "MenuGraphics.h"
#include "Board.h"
#include "Manager.h"
#include "Mario.h"
#include <vector>
#include <memory>

/*
* This class represents the enemies manager in the game and responsible for managing all enemies in the game.
* It inherits from Manager class.
*/


class EnemiesManager : public Manager
{
	static constexpr int MAX_BARRELS = 20;      // max number of barrels in a game
	static constexpr int BARRELS_PACE = 700;    // pace at which barrels are activated

	std::vector<std::unique_ptr<Enemy>> enemies;

	Mario* pMario = nullptr;	// to get mario location and move accordingly

	int sleepCount = 0;			// counter to keep track of the pace of the activation
	int activated_I = 1;		// index of the next barrel to be activated
public:
	EnemiesManager(Board b, MenuGraphics* mg, Mario* mario) : Manager(b, mg) {
		setMario(mario);
	};
	~EnemiesManager() {};

	// virtual functions
	void reset(Board& board, Mario* pMario = nullptr) override;
	void draw(Mario& mario) override;
	void move(Mario& mario) override;

	// Additional methods
	void smashEnemies(Mario& mario);
	void barrelsActivation();
	void setMario(Mario* mario) { pMario = mario; }
};

