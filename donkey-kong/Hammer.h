#pragma once
#include "Entity.h"
#include "Board.h"

class Hammer : public Entity
{
	static constexpr char HAMMER_CHAR = 'p';
	static constexpr int MAX_SLEEP = 500;
	static constexpr int SLEEP_STEP = 50;

	bool active = true; // if is active mario can pick it up and smash barrels
	bool collected = false;

	int sleepCounter = 0;

public:
	Hammer(Board* board) : Entity(board) {
		placeRandomly(*board);
	}
	
	//void activate();
	
	//void deactivate() {
	//	active = false;
	//}

	void draw() const {
		if (!collected)
			Entity::draw(HAMMER_CHAR);
	}
	void erase() {
		if (collected)
			Entity::erase();
	}

	void setCollected(bool b) {
		collected = b;
	}

	bool isCollected() const {
		return collected;
	}
	/*bool isActive() const {
		return active;
	}*/

	/*bool isPickedUp() const {
		return pickedUp;
	}*/

	//void pickUp() {
	//	pickedUp = true;
	//	active = false; // so hammer don't show on board
	//}

	void placeRandomly(Board& board);
};

