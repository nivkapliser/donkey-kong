#pragma once
#include "Entity.h"

class Hammer: public Entity
{

	bool isActive = false; // if is active mario can pick it up and smash barrels
public:
	Hammer(int x, int y, Board* pBoard) : Entity(x, y, pBoard, 'p') {}
	
	void setRandomPosition() {
		;
	}

	bool checkActivation() const {
		return isActive;
	}
	
	void setActivation(bool x) {
		isActive = x;
	}
};

