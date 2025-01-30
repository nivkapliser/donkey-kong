#pragma once
#include "Enemy.h"
#include "Mario.h"

/*
* This class represents the SpacialGhost enemy in the game. 
* The SpacialGhost is a ghost that moves in a straight line towards Mario.
* It can climb up and down ladders to reach him.
*/

class SpacialGhost : public Enemy {

	Mario* pMario = nullptr; // to get mario location and move accordingly

public:
	SpacialGhost(Mario* _mario) : Enemy('X', true) {  
		setMario(_mario); 
		setDirectionToMario();
	}
	~SpacialGhost() {}

	// virtual functions
	void move() override;
	void erase() override;
	void reset(Board& board) override;
	void deactivation() override;
	void explode() override;
	bool checkEncounters(Mario& mario) override;

	// getters and setters
	void setMario(Mario* _pMario) { pMario = _pMario; }
	int getMarioX() const { return pMario->getX(); }
	void setDirectionToMario();
	bool isFloorEnd() const;
};


