#include "BarrelManager.h"

void BarrelManager::resetBarrels(Board& board)
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		barrels[i].setBoard(board);
	}
}

// shoud be in barrel class?
void BarrelManager::drawBarrels(Mario& mario)
{
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true)
		{
			barrels[i].draw();
			barrels[i].floorDirSync();
			if (barrels[i].barrelFallManager() == true)
				barrels[i].explode();

			if (barrels[i].checkEncounters(mario))
				if (mario.getLives() == 1) {
					//currentState = GAME_OVER;
					mario.downLives();
				}
				else {
					Sleep(250);
					//resetStage();
					mario.downLives();
				}
		}
	}
}


// should be in barrel class?
void BarrelManager::moveBarrels(Mario& mario)
{
	for (int i = 0; i <= MAX_BARRELS; i++)
	{
		if (barrels[i].checkActivationStatus() == true)
		{

			if (barrels[i].checkEncounters(mario))
				if (mario.getLives() == 1) {
					//currentState = GAME_OVER;
					mario.downLives();
				}
				else {
					Sleep(250);
					//resetStage();
					mario.downLives();
					//mario.eraseLife();
					//mario.drawLife();
				}
			//resetStage();
			barrels[i].erase();
			barrels[i].move();
		}

	}
}

// should be in barrel class?
void BarrelManager::barrelsActivation() {
	static int sleepCount = 0;
	static int activatedBarrel = 1;

	if (sleepCount == BARRELS_PACE) // need a separate function for this?
	{
		if (barrels[activatedBarrel].checkActivationStatus() == false)
		{
			barrels[activatedBarrel].barrelActivation();
			activatedBarrel++;
		}
		if (activatedBarrel == MAX_BARRELS)
			activatedBarrel = 0;
		sleepCount = 0;

	}
	sleepCount += 50;
}