#include "GhostManager.h"

// Function to reset the barrels array and set the board for each barrel
void GhostManager::resetGhosts(Board& board)
{
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		ghosts[i] = Ghost();
		ghosts[i].setBoard(board);
	}
}

// Function to draw all the active barrels on the board 
void GhostManager::drawGhosts(Mario& mario)
{
	menuGraphics->setCurrentColor(menuGraphics->getCyan());
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		ghosts[i].draw();

		if (ghosts[i].checkEncounters(mario)) { // if barrel encounters mario
			encounters = true;
		}
	}

	menuGraphics->setCurrentColor(menuGraphics->getLightRed());
}

// Function to move all the active barrels on the board
void GhostManager::moveGhosts(Mario& mario)
{
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		if (ghosts[i].checkEncounters(mario)) { // if barrel encounters mario
			encounters = true;
		}
		ghosts[i].erase();
		ghosts[i].move();


	}
}

// Function to activate the barrels at a certain pace (BARRELS_PACE)
void GhostManager::ghostsActivation() {

	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		ghosts[activatedGhost].ghostActivation();
	}

}