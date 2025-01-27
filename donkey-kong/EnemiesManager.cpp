#include "EnemiesManager.h"
#include "Barrel.h"
#include "Ghost.h"
#include "SpacialGhost.h"
#include "Mario.h"

void EnemiesManager::reset(Board& board) {
	//resetLocationMap(); -- should see how to implement this

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
		ghost->setIndex(MAX_BARRELS + i);
        ghost->setBoard(board);
        ghost->setX(board.getGhostX(i));
        ghost->setY(board.getGhostY(i));
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
//
//void GhostManager::move(Mario& mario)
//{
//	int next_location;
//
//	for (size_t i = 1; i < ghosts.size(); i++)
//	{
//		if (ghosts[i].checkEncounters(mario)) {
//			setEncounters(true);
//		}
//
//		int nextY = ghosts[i].getY() + ghosts[i].getDirY();
//		int nextX = ghosts[i].getX() + ghosts[i].getDirX();
//		next_location = ghostsLocationsMap[nextY][nextX];
//
//		if (next_location != 0)
//		{
//			ghosts[i].switchGhostsMeeting();
//			ghosts[next_location].switchGhostsMeeting();
//		}
//
//		ghosts[i].erase();
//		//the current ghost will move, so his current cell becomes 0
//		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = 0;
//
//		ghosts[i].move();
//
//		ghostsLocationsMap[ghosts[i].getY()][ghosts[i].getX()] = i; //update the ghosts location table
//
//	}


// Additional methods
void EnemiesManager::addEnemy(std::unique_ptr<Enemy> enemy){}
void EnemiesManager::smashEnemies(Mario& mario){}