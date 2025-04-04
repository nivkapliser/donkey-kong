#include "EnemiesManager.h"
#include "Barrel.h"
#include "Ghost.h"
#include "SpacialGhost.h"
#include "Mario.h"

// Function to reset the manager with all the enemies
void EnemiesManager::reset(Board& board, Mario* pMario) {
	enemies.clear();
    for (int i = 0; i < MAX_BARRELS; ++i)
    {
        auto barrel = std::make_unique<Barrel>();
        barrel->setBoard(board);
        enemies.push_back(std::move(barrel));   
    }

    for (int i = 0; i < board.getNumGhosts(); ++i)
    {
        auto ghost = std::make_unique<Ghost>();
		ghost->reset(board);
        ghost->setX(board.getGhostX(i));
        ghost->setY(board.getGhostY(i));
        enemies.push_back(std::move(ghost));
    }

	for (int i = 0; i < board.getNumSpacialGhosts(); ++i) {
		auto spacialGhost = std::make_unique<SpacialGhost>(pMario);
		spacialGhost->reset(board, pMario);
		spacialGhost->setX(board.getSpacialGhostX(i));
		spacialGhost->setY(board.getSpacialGhostY(i));
		enemies.push_back(std::move(spacialGhost));
	}

}

// Function to draw all the enemies
void EnemiesManager::draw(Mario& mario) {

	for (auto& enemy : enemies)
	{	
		if (typeid(*enemy) == typeid(Ghost)) {
			getMG()->setCurrentColor(getMG()->getCyan());
		}
		else
			getMG()->setCurrentColor(getMG()->getBrown());

		if (enemy->checkActivationStatus()) 
		{
			enemy->draw();
			if (enemy->checkEncounters(mario))
			{
				setEncounters(true);
			}
		}
	}
	getMG()->setCurrentColor(getMG()->getLightRed());

}

// Function to move all the enemies
void EnemiesManager::move(Mario& mario) {
	for (auto& enemy : enemies)
	{
		if (enemy->checkActivationStatus())
		{
			if (enemy->checkEncounters(mario))
			{
				setEncounters(true);
			}
			if (!enemy->getBoard().getSilent()) enemy->erase();
			enemy->move();
			if (enemy->checkEncounters(mario))
			{
				setEncounters(true);
			}
		}
	}
}

// Function to smash the enemies if mario uses the hammer
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
				if (!enemy->getBoard().getSilent()) {
					enemy->erase();

					if (typeid(*enemy) == typeid(Ghost))
						enemy->printAnimation("SMASH!!", "_\\x/_");
					else if (typeid(*enemy) == typeid(Barrel))
						enemy->printAnimation("SMASH!!", "_\\O/_");
					else if (typeid(*enemy) == typeid(SpacialGhost))
						enemy->printAnimation("SMASH!!", "_\\X/_");
				}
				enemy->deactivation();
				mario.increaseScore(typeid(*enemy) == typeid(Barrel) ? 
									mario.getBarrelPoints() : mario.getGhostPoints());
			}
		}
	}
}

// Function to activate the barrels
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