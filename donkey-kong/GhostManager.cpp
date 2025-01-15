#include "GhostManager.h"


void GhostManager::reset(Board& board) {
	resetLocationMap(); //very very important!! 
	ghosts.clear();

	ghosts.push_back(Ghost()); //dummy ghost to keep index 0 free.

	for (size_t i = 0; i < board.getNumGhosts(); i++) {
		Ghost ghost;
		ghost.setBoard(board);
		ghost.setX(board.getGhostX(i));
		ghost.setY(board.getGhostY(i));
		ghosts.push_back(ghost);
	}
}

// Function to draw all the active barrels on the board 
void GhostManager::draw(Mario& mario)
{
	getMG()->setCurrentColor(getMG()->getCyan());
	for (int i = 1; i < ghosts.size(); i++)
	{
		if (ghosts[i].checkActivationStatus()) {
			ghosts[i].draw();

			if (ghosts[i].checkEncounters(mario)) { // if barrel encounters mario
				setEncounters(true);
			}
		}
	}

	getMG()->setCurrentColor(getMG()->getLightRed());
}

// Function to move all the active barrels on the board
void GhostManager::move(Mario& mario)
{
	int next_location;

	for (size_t i = 1; i < ghosts.size(); i++)
	{
		if (ghosts[i].checkEncounters(mario)) {
			setEncounters(true);
		}

		int nextY = ghosts[i].getY() + ghosts[i].getDirY();
		int nextX = ghosts[i].getX() + ghosts[i].getDirX();	
		next_location = ghostsLocationsMap[nextY][nextX];

		if (next_location != 0)
		{
			ghosts[i].switchGhostsMeeting();
			ghosts[next_location].switchGhostsMeeting();
		}

		ghosts[i].erase();
		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = 0; //the current ghost will move, so his current cell becomes 0

		ghosts[i].move();

		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = i; //update the ghosts location table

	}
}

void GhostManager::smashGhosts(Mario& mario) {
	for (size_t i = 1; i < ghosts.size(); i++) {
		if (mario.getDirX() == -1) {
			if ((ghosts[i].getY() == mario.getY()) &&
				((ghosts[i].getX() == mario.getX() - 1) ||
					(ghosts[i].getX() == mario.getX() - 2)))
			{
				// Erase ghost from screen
				ghosts[i].erase();
				ghosts[i].activation(false);
				// earase ghost from vector
				ghosts.erase(ghosts.begin() + i);
				mario.increaseScore(mario.getGhostPoints());
			}
		}
		else if (mario.getDirX() == 1) {
			if ((ghosts[i].getY() == mario.getY()) &&
				((ghosts[i].getX() == mario.getX() + 1) ||
					(ghosts[i].getX() == mario.getX() + 2)))
			{
				// Erase ghost from screen
				ghosts[i].erase();
				ghosts[i].activation(false);
				// earase ghost from vector
				ghosts.erase(ghosts.begin() + i);
				mario.increaseScore(mario.getGhostPoints());
			}
		}
	}
}
void GhostManager::resetLocationMap()
{
	for (size_t i = 1; i < ghosts.size(); i++)
	{
		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = 0;
	}
}

