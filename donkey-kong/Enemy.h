#pragma once
#include "Board.h"
#include "Mario.h"
#include "utils.h"

/*
* This class represents an entity in the game. 
* every specific entity will inherit from this class.
*/

class Enemy
{
	static constexpr char EMPTY_SPACE = ' ';

	char ch;
	int x = 0;
	int y = 0;

	int dirX = 0;
	int dirY = 0;

	bool active; // for the barrelsManager to check if the barrel is active
	char lastPoint; // to save the last point char for latter printing

	bool encountered = false;

	Board* pBoard = nullptr;


	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

protected: // need to decide
	enum Direction { LEFT, RIGHT, SAME, STOP }; //very helps when in public, need to check if its ok

public:
	Enemy(char _c, bool _active, int start_y = 0, int start_x = 0) : ch(_c), active(_active), x(start_x), y(start_y) {} // need to change to no default values

	virtual ~Enemy() = default;

	int getX() const { return x; }
	int getY() const { return y; }	
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	void setChar(char _c) { ch = _c; }
	int getDirX() const { return dirX; }
	int getDirY() const { return dirY; }
	void setDirX(int _dirX) { dirX = _dirX; }
	void setDirY(int _dirY) { dirY = _dirY; }


	virtual void draw() const { draw(ch); }
	virtual void erase() {
		setLastPoint();
		draw(lastPoint);
	}

	void setLastPoint() { lastPoint = pBoard->getChar(x, y); }
	void setBoard(Board& board) { pBoard = &board; }
	bool checkActivationStatus() const { return active; }

	Board& getBoard() const { return *pBoard; }

	virtual void changeDir(Direction dir);
	virtual void move() = 0;
	
	virtual void resetLocation(int start_x, int start_y) { x = start_x; y = start_y; }
	virtual void activation(bool b) { active = b; }; //need to be Enemy activator
	virtual bool checkEncounters(Mario& mario);
	int getDirectionRandomly() const;
	void setEncountered(bool b) { encountered = b; }
	bool isEncountered() { return encountered; }
	virtual bool reachedBottom();

	//virtual void handleCollision() = 0;
};

