#pragma once
#include "Enemy.h"
#include "Mario.h"

class SpacialGhost : public Enemy {
	Mario* pMario = nullptr; // to get mario location and move accordingly

public:
	SpacialGhost(Mario* _mario) : Enemy('*', true, 11, 50) { 
		setMario(_mario); 
		setDirectionToMario();
	}

	void move() override;
	
	void setMario(Mario* _pMario) { pMario = _pMario; }
	int getMarioX() const { return pMario->getX(); }
	void setDirectionToMario();
	bool isFloorEnd() const;

};


