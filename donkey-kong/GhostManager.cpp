#include "GhostManager.h"

// Function to reset the barrels array and set the board for each barrel
void GhostManager::resetGhosts(Board& board)
{
	for (int i = 1; i < MAX_GHOSTS; i++)
	{
		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = 0; //init the locations table
		ghosts[i] = Ghost();  //we will delete it soon when we will put the ghosts locations on the screen file, its just for now.
		ghosts[i].setBoard(board);
		ghosts[i].resetLocation(board.getGhostX(i), board.getGhostY(i));
	}
}

// Function to draw all the active barrels on the board 
void GhostManager::drawGhosts(Mario& mario)
{
	menuGraphics->setCurrentColor(menuGraphics->getCyan());
	for (int i = 1; i < MAX_GHOSTS; i++)
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
	int next_location;

	for (int i = 1; i < MAX_GHOSTS; i++)
	{
		if (ghosts[i].checkEncounters(mario)) {
			encounters = true;
		}

		next_location = ghostsLocationsMap[ghosts[i].getY() + ghosts[i].getDirY()][ghosts[i].getX() + ghosts[i].getDirX()];
		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = 0; //the current ghost will move, so his current cell becomes 0

		if (next_location != 0)
		{
			ghosts[i].switchGhostsMeeting();
			ghosts[next_location].switchGhostsMeeting();
		}

		ghosts[i].erase();
		ghosts[i].move();

		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = i; //update the ghosts location table

	}
}


void GhostManager::ghostsActivation() { //function to get rid of, after putting the ghosts in screen file

	for (int i = 1; i < MAX_GHOSTS; i++)
	{
		ghosts[activatedGhost].ghostActivation();
	}

}