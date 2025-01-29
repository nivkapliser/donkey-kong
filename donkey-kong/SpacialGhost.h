#pragma once
#include "Enemy.h"
#include "Mario.h"

class SpacialGhost : public Enemy {
	Mario* pMario = nullptr; // to get mario location and move accordingly

public:
	SpacialGhost(Mario* _mario) : Enemy('X', true) {  
		setMario(_mario); 
		setDirectionToMario();
	}

	void move() override;
	void erase() override;
	void reset(Board& board) override;

	void setMario(Mario* _pMario) { pMario = _pMario; }
	int getMarioX() const { return pMario->getX(); }
	void setDirectionToMario();
	bool isFloorEnd() const;

	void deactivation() override;
	void explode() override;
	bool checkEncounters(Mario& mario) override;

};


