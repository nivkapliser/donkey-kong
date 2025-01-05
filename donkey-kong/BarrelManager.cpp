#include "BarrelManager.h"

// Function to reset the barrels array and set the board for each barrel
void BarrelManager::resetBarrels(Board& board)
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		barrels[i] = Barrel();
		barrels[i].setBoard(board);
	}
}

// Function to draw all the active barrels on the board 
void BarrelManager::drawBarrels(Mario& mario)
{
	menuGraphics->setCurrentColor(menuGraphics->getBrown());
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true)
		{
			barrels[i].draw();
			barrels[i].floorDirSync();
			if (barrels[i].barrelFallManager() == true) // if barrel fell 8 lines
				barrels[i].explode();

			if (barrels[i].checkEncounters(mario)) { // if barrel encounters mario
				encounters = true; 
			}
		}
	}
	menuGraphics->setCurrentColor(menuGraphics->getLightRed());
}

// Function to move all the active barrels on the board
void BarrelManager::moveBarrels(Mario& mario)
{
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true) // if barrel is active
		{
			if (barrels[i].checkEncounters(mario)) { // if barrel encounters mario
				encounters = true; 
			}
			barrels[i].erase();
			barrels[i].move();
		}

	}
}

// Function to activate the barrels at a certain pace (BARRELS_PACE)
void BarrelManager::barrelsActivation() {

	if (sleepCount == BARRELS_PACE) 
	{
		if (barrels[activatedBarrel].checkActivationStatus() == false) // if barrel is not active
		{
			barrels[activatedBarrel].barrelActivation();
			activatedBarrel++;
		}
		if (activatedBarrel == MAX_BARRELS)
			activatedBarrel = 0; // reset the activated barrel index
		sleepCount = 0; // reset the sleep count

	}
	sleepCount += 50; // increment the sleep count
}

void BarrelManager::smashBarrels(Mario& mario) {
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true) // if barrel is active
		{
			if (mario.getSmash()) {
				if (mario.getX() + 1 == barrels[i].getX() || mario.getX() - 1 == barrels[i].getX() && mario.getY() == barrels[i].getY()) {
					barrels[i].erase();
					barrels[i].explode();
				}
			}
		}
	}
}