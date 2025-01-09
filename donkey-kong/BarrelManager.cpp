#include "BarrelManager.h"

// Function to reset the barrels array and set the board for each barrel
void BarrelManager::resetBarrels(Board& board)
{
	for (auto& barrel : barrels) {
		barrel = Barrel();
		barrel.setBoard(board);
	}
}

// Function to draw all the active barrels on the board 
void BarrelManager::drawBarrels(Mario& mario)
{
	menuGraphics->setCurrentColor(menuGraphics->getBrown());
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
				encounters = true;
			}
		}
	}
	menuGraphics->setCurrentColor(menuGraphics->getLightRed());
}

// Function to move all the active barrels on the board
void BarrelManager::moveBarrels(Mario& mario)
{
	for (auto& barrel : barrels) {
		if (barrel.checkActivationStatus()) {
			if (barrel.checkEncounters(mario)) {	
				encounters = true;
			}
			barrel.erase();	
			barrel.move();	
		}	
	}
}

// Function to activate the barrels at a certain pace (BARRELS_PACE)
void BarrelManager::barrelsActivation() {
	if (sleepCount == BARRELS_PACE) {
		if (!barrels[activatedBarrel].checkActivationStatus()) {
			//barrels[activatedBarrel] = Barrel();
			//barrels[activatedBarrel].setBoard(board);
			barrels[activatedBarrel].barrelActivation();
			activatedBarrel++;
		}
		if (activatedBarrel >= barrels.size()) {
			activatedBarrel = 0;
		}
		sleepCount = 0;
	}
	sleepCount += 50;
}


void BarrelManager::smashBarrels(Mario& mario) {
	for (auto& barrel : barrels) {
		if (barrel.checkActivationStatus()) {
			if ((barrel.getY() == mario.getY()) &&
				((barrel.getX() == mario.getX() + 1) || (barrel.getX() == mario.getX() - 1))) {
				barrel.erase();
				barrel.explode();
				barrel.barrelDeactivation();
			}
		}
	}
}
