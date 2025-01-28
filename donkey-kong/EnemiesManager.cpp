#include "EnemiesManager.h"
#include "Barrel.h"
#include "Ghost.h"
#include "SpacialGhost.h"
#include "Mario.h"

void EnemiesManager::reset(Board& board) {
	//resetLocationMap();// -- should see how to implement this

	enemies.clear();
    for (int i = 0; i < MAX_BARRELS; ++i)
    {
        auto barrel = std::make_unique<Barrel>();
        // set its board, initial position, etc.
        barrel->setBoard(board);
        enemies.push_back(std::move(barrel));   
    }

    for (int i = 0; i < board.getNumGhosts(); ++i)
    {
        auto ghost = std::make_unique<Ghost>();
		//ghost->setIndex(MAX_BARRELS + i);
		ghost->reset(board); //enemy virtual func, resets the board and the ghost place in location map 
        ghost->setX(board.getGhostX(i));
        ghost->setY(board.getGhostY(i));
		ghost->setGhostInLocationMap();
        enemies.push_back(std::move(ghost));
    }

    //// Maybe add 1 spacial ghost for debug -- need to check this 
    //auto spacialGhost = std::make_unique<SpacialGhost>(&pMario /* if you pass Mario* */);
    //spacialGhost->setBoard(board);
    //// set position
    //enemies.push_back(std::move(spacialGhost));
}
void EnemiesManager::draw(Mario& mario) { // need to add colors
	for (auto& enemy : enemies)
	{
		if (enemy->checkActivationStatus()) 
		{
			enemy->draw();
			if (enemy->checkEncounters(mario))
			{
				setEncounters(true);
			}
		}
	}
}
void EnemiesManager::move(Mario& mario) {
	for (auto& enemy : enemies)
	{
		if (enemy->checkActivationStatus())
		{
			if (enemy->checkEncounters(mario))
			{
				setEncounters(true);
			}
			enemy->erase();
			enemy->move();
			if (enemy->checkEncounters(mario))
			{
				setEncounters(true);
			}
		}
	}
}

// Additional methods
void EnemiesManager::addEnemy(std::unique_ptr<Enemy> enemy){}
void EnemiesManager::smashEnemies(Mario& mario){
	for (auto& enemy : enemies)
	{
		if (enemy->checkActivationStatus())
		{
			bool shouldSmash = false;
			// facing left
			if (mario.getDirX() == -1) {
			    shouldSmash = (enemy->getY() == mario.getY()) &&
			        (enemy->getX() >= mario.getX() - 3 && enemy->getX() < mario.getX());
			}
			// facing right
			else if (mario.getDirX() == 1) {
			    shouldSmash = (enemy->getY() == mario.getY()) &&
			        (enemy->getX() <= mario.getX() + 3 && enemy->getX() > mario.getX());
			}
			
			// the smash control
			if (shouldSmash) {
				enemy->erase();
				enemy->printAnimation("SMASH!!", "_\\O/_"); // type_id
				enemy->deactivation();
			    mario.increaseScore(mario.getBarrelPoints()); // need to think (type_id)
			}
		}
	}
}

void EnemiesManager::barrelsActivation() {
	if (sleepCount == BARRELS_PACE) {
		if (!enemies[activated_I]->checkActivationStatus()) {
			if (!enemies[activated_I]->checkActivationStatus())
			{
				enemies[activated_I]->setExploding(false);	
				enemies[activated_I]->activation(true);	
				if (getRandomIntInRange(1) == 1)
					enemies[activated_I]->setX(enemies[activated_I]->getBoard().getDonkeyKongX() + 1); // for the start position of the barrel
				else
					enemies[activated_I]->setX(enemies[activated_I]->getBoard().getDonkeyKongX() - 1); // for the start position of the barrel
				enemies[activated_I]->setY(enemies[activated_I]->getBoard().getDonkeyKongY());
			}
			activated_I++;
		}
		if (activated_I >= MAX_BARRELS) {
			activated_I = 0;
		}
		sleepCount = 0;
	}
	sleepCount += 50;
}