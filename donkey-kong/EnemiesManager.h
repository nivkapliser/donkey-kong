#pragma once
#include "Enemy.h"
#include "MenuGraphics.h"
#include "Board.h"
#include <vector>
#include <memory>
#include "Manager.h"
#include "Mario.h"

class EnemiesManager : public Manager
{
	static constexpr int MAX_BARRELS = 20;      // max number of barrels in a game
	static constexpr int BARRELS_PACE = 700;    // pace at which barrels are activated

	std::vector<std::unique_ptr<Enemy>> enemies;
	//int ghostsLocationsMap[26][80] = { 0 }; // for ghost meeting - maybe implement with loops

	Mario* pMario = nullptr; // to get mario location and move accordingly

public:
	EnemiesManager(Board b, MenuGraphics* mg) : Manager(b, mg) {};
	~EnemiesManager() {};

	void reset(Board& board) override;
	void draw(Mario& mario) override;
	void move(Mario& mario) override;

	// Additional methods
	void addEnemy(std::unique_ptr<Enemy> enemy);
	void smashEnemies(Mario& mario);

	// Manager's methods:..
};

