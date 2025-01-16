#include "BarrelManager.h"

void BarrelManager::reset(Board& board) {
    barrels.clear();
    for (int i = 0; i < MAX_BARRELS; i++) {
        Barrel barrel;
        barrel.setBoard(board);
        barrels.push_back(barrel);
    }
}

void BarrelManager::draw(Mario& mario) {
    getMG()->setCurrentColor(getMG()->getBrown());
    for (auto& barrel : barrels) {
        if (barrel.checkActivationStatus()) {
            barrel.draw();
            barrel.floorDirSync(); 

            if (barrel.barrelFallManager()) {
                barrel.explode();
            }

            if (barrel.checkEncounters(mario)) {
                setEncounters(true);
            }
        }
    }
    getMG()->setCurrentColor(getMG()->getLightRed());
}

void BarrelManager::move(Mario& mario) {
    for (auto& barrel : barrels) {
        if (barrel.checkActivationStatus()) {
            barrel.erase();
            barrel.move();
            if (barrel.checkEncounters(mario)) {
                setEncounters(true);
            }
        }
    }
}

void BarrelManager::barrelsActivation() {
    if (getSleepCount() == BARRELS_PACE) {
        if (!barrels[getActivatedIndex()].checkActivationStatus()) {
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
        if (mario.getDirX() == -1) {
            if (barrel.checkActivationStatus() && (barrel.getY() == mario.getY()) &&
                ((barrel.getX() == mario.getX() - 3) ||
                    (barrel.getX() == mario.getX() - 2))) {
                //barrel.erase(); //deactivation erase it automatically
                //barrel.explode();
                barrel.printAnimation("SMASH!!", "_\\O/_");
                barrel.barrelDeactivation();
                mario.increaseScore(mario.getBarrelPoints());
            }
        }
        else if (mario.getDirX() == 1) {
            if (barrel.checkActivationStatus() && (barrel.getY() == mario.getY()) &&
                ((barrel.getX() == mario.getX() + 3) ||
                    (barrel.getX() == mario.getX() + 2))) {
                //barrel.erase();
                //barrel.explode();
                barrel.printAnimation("SMASH!!", "_\\O/_");
                barrel.barrelDeactivation();
                mario.increaseScore(mario.getBarrelPoints());
            }
        }
    }
}

//// Function to reset the barrels array and set the board for each barrel
//void BarrelManager::reset(Board& board)
//{	
//	for (auto& barrel : barrels) {
//		barrel = Barrel();
//		barrel.setBoard(board);
//	}
//}
//
//// Function to draw all the active barrels on the board 
//void BarrelManager::draw(Mario& mario)
//{
//	getMG()->setCurrentColor(getMG()->getBrown());
//	for (auto& barrel : barrels) {
//		if (barrel.checkActivationStatus()) {
//			barrel.draw();
//			barrel.floorDirSync();
//			if (barrel.barrelFallManager()) {
//				barrel.explode();
//			}
//			if (barrel.checkEncounters(mario)) {
//				setEncounters(true);
//			}
//		}
//	}
//	getMG()->setCurrentColor(getMG()->getLightRed());
//}
//
//// Function to move all the active barrels on the board
//void BarrelManager::move(Mario& mario)
//{
//	for (auto& barrel : barrels) {
//		if (barrel.checkActivationStatus()) {
//			barrel.erase();	
//			barrel.move();	
//			if (barrel.checkEncounters(mario)) {
//				setEncounters(true);
//			}
//		}	
//	}
//}
//
//// Function to activate the barrels at a certain pace (BARRELS_PACE)
//void BarrelManager::barrelsActivation() {
//	if (getSleepCount() == BARRELS_PACE) {
//		if (!barrels[getActivatedIndex()].checkActivationStatus()) {
//			barrels[getActivatedIndex()].barrelActivation();
//			setActivatedIndex(getActivatedIndex() + 1);
//		}
//		if (getActivatedIndex() >= barrels.size()) {
//			setActivatedIndex(0);
//		}
//		setSleepCount(0);
//	}
//	setSleepCount(getSleepCount() + 50);
//}
//
//
//void BarrelManager::smashBarrels(Mario& mario) {
//
//	for (auto& barrel : barrels) {
//		if (mario.getDirX() == -1) {
//			if ((barrel.getY() == mario.getY()) &&
//				((barrel.getX() == mario.getX() - 3) || (barrel.getX() == mario.getX() - 2))) {
//				barrel.erase();
//				barrel.explode();
//				barrel.barrelDeactivation();
//				mario.increaseScore(mario.getBarrelPoints());
//			}
//		}
//		else if (mario.getDirX() == 1) {
//			if ((barrel.getY() == mario.getY()) &&
//				((barrel.getX() == mario.getX() + 3) || (barrel.getX() == mario.getX() + 2))) {
//				barrel.erase();
//				barrel.explode();
//				barrel.barrelDeactivation();
//				mario.increaseScore(mario.getBarrelPoints());
//			}
//		}
//	}
//}
