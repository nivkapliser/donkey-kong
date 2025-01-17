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
            if (barrel.checkEncounters(mario)) {
                setEncounters(true);
            }
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
        if (!barrel.checkActivationStatus()) {
            continue;  // Skip inactive barrels
        }

        bool shouldSmash = false;
        if (mario.getDirX() == -1) {  // Facing left
            shouldSmash = (barrel.getY() == mario.getY()) &&
                (barrel.getX() >= mario.getX() - 3 && barrel.getX() < mario.getX());
        }
        else if (mario.getDirX() == 1) {  // Facing right
            shouldSmash = (barrel.getY() == mario.getY()) &&
                (barrel.getX() <= mario.getX() + 3 && barrel.getX() > mario.getX());
        }

        if (shouldSmash) {
            barrel.erase();
            barrel.printAnimation("SMASH!!", "_\\O/_");
            barrel.barrelDeactivation();
            mario.increaseScore(mario.getBarrelPoints());
        }
    }
}



