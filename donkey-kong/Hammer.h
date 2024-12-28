#pragma once
#include "Entity.h"
#include "Board.h"

class Hammer: public Entity
{
	static constexpr char HAMMER_CHAR = 'p';
	static constexpr int MAX_SLEEP = 500;
	static constexpr int SLEEP_STEP = 50;

	bool active = false; // if is active mario can pick it up and smash barrels
	bool pickedUp = false;

	int sleepCounter = 0;

public:
	Hammer(int x, int y, Board* pBoard) : Entity(x, y, pBoard, 'p')
	{
		active = true;
	}
	
	void activate();
	void deactivate() {
		active = false;
	}

	bool isActive() const {
		return active;
	}

	bool isPickedUp() const {
		return pickedUp;
	}

	void pickUp() {
		pickedUp = true;
		active = false; // so hammer don't show on board
	}

	void placeRandomly(Board& board);
};

