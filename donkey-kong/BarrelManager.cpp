#include "BarrelManager.h"

// Function to reset the barrels array and set the board for each barrel
void BarrelManager::reset(Board& board)
{
	for (auto& barrel : barrels) {
		barrel = Barrel();
		barrel.setBoard(board);
	}
}

// Function to draw all the active barrels on the board 
void BarrelManager::draw(Mario& mario)
{
	getMG()->setCurrentColor(getMG()->getBrown());
	for (auto& barrel : barrels) {
		if (barrel.checkActivationStatus()) {
			barrel.draw();
			barrel.floorDirSync();
			if (barrel.barrelFallManager()) {
				barrel.explode();
				//barrel.setY(board.getDonkeyKongY());
				//barrel.setX(board.getDonkeyKongX());
			}
			if (barrel.checkEncounters(mario)) {
				setEncounters(true);
			}
		}
	}
	getMG()->setCurrentColor(getMG()->getLightRed());
}

// Function to move all the active barrels on the board
void BarrelManager::move(Mario& mario)
{
	for (auto& barrel : barrels) {
		if (barrel.checkActivationStatus()) {
			if (barrel.checkEncounters(mario)) {	
				setEncounters(true);
			}
			barrel.erase();	
			barrel.move();	
		}	
	}
}

// Function to activate the barrels at a certain pace (BARRELS_PACE)
void BarrelManager::barrelsActivation() {
	if (getSleepCount() == BARRELS_PACE) {
		if (!barrels[getActivatedIndex()].checkActivationStatus()) {
			//barrels[activatedBarrel] = Barrel();
			//barrels[activatedBarrel].setBoard(board);
			barrels[getActivatedIndex()].barrelActivation();
			setActivatedIndex(getActivatedIndex() + 1);
		}
		if (getActivatedIndex() >= barrels.size()) {
			setActivatedIndex(0);
		}
		setSleepCount(0);
	}
	setSleepCount(getSleepCount() + 50);
}


void BarrelManager::smashBarrels(Mario& mario) {
	for (auto& barrel : barrels) {
		if (barrel.checkActivationStatus()) {
			if ((barrel.getY() == mario.getY()) &&
				((barrel.getX() == mario.getX() + 1) || (barrel.getX() == mario.getX() - 1) ||
					(barrel.getX() == mario.getX() + 2) || barrel.getX() == mario.getX() - 2)) {
				barrel.erase();
				barrel.explode();
				barrel.barrelDeactivation();
				mario.increaseScore(mario.getBarrelPoints());
			}
		}
	}
}
