#include "GhostManager.h"


void GhostManager::initGhosts(Board& board) {
	ghosts.clear();
	for (size_t i = 0; i < board.getNumGhosts(); i++) {
		Ghost ghost;
		ghost.setBoard(board);
		ghost.setX(board.getGhostX(i));
		ghost.setY(board.getGhostY(i));
		ghost.activation(true);
		ghosts.push_back(ghost);
	}
}


// Function to reset the barrels array and set the board for each barrel
void GhostManager::resetGhosts(Board& board)
{
	for (auto& ghost : ghosts) {
		ghost.setBoard(board);
	}
}

// Function to draw all the active barrels on the board 
void GhostManager::drawGhosts(Mario& mario)
{
	menuGraphics->setCurrentColor(menuGraphics->getCyan());
	for (auto& ghost : ghosts)
	{
		if (ghost.isActive()) {
			ghost.draw();

			if (ghost.checkEncounters(mario)) { // if barrel encounters mario
				encounters = true;
			}
		}
	}

	menuGraphics->setCurrentColor(menuGraphics->getLightRed());
}

// Function to move all the active barrels on the board
void GhostManager::moveGhosts(Mario& mario)
{
	int next_location;

	for (size_t i = 0; i < ghosts.size(); i++)
	{
		if (ghosts[i].checkEncounters(mario)) {
			encounters = true;
		}

		next_location = ghostsLocationsMap[ghosts[i].getY() + ghosts[i].getDirY()][ghosts[i].getX() + ghosts[i].getDirX()]; // change
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

void GhostManager::smashGhosts(Mario& mario) {
	for (size_t i = 0; i < ghosts.size(); i++) {
		if ((ghosts[i].getY() == mario.getY()) &&
			((ghosts[i].getX() == mario.getX() + 1) ||
				(ghosts[i].getX() == mario.getX() - 1)))
		{
			// Erase ghost from screen
			ghosts[i].erase();

			ghosts[i].activation(false);
			// earase ghost from vector
			ghosts.erase(ghosts.begin() + i);

			// or could do:
			//ghosts[i] = Ghost();  // basically "kill" it
		}
	}
}

