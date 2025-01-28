#pragma once
#include "Board.h"
#include "Mario.h"
#include "utils.h"

/*
* This class represents Mario's enemy in the game. 
* every specific enemy will inherit from this class.
*/

class Enemy
{
	static constexpr char EMPTY_SPACE = ' ';

	char ch;
	int x = 0;
	int y = 0;

	int dirX = 0;
	int dirY = 0;

	bool active; 
	char lastPoint; 
	bool encountered = false;
	bool exploding = false;

	Board* pBoard = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

protected: 
	enum class Direction { LEFT, RIGHT, SAME, STOP }; // to set the direction of the entity

public:
	Enemy(char _c, bool _active, int start_y = 0, int start_x = 0) : ch(_c), active(_active),
		x(start_x), y(start_y) {} 
	virtual ~Enemy() = default;

	// some getters and setters
	int getX() const { return x; }
	int getY() const { return y; }	
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	void setChar(char _c) { ch = _c; }
	int getDirX() const { return dirX; }
	int getDirY() const { return dirY; }
	void setDirX(int _dirX) { dirX = _dirX; }
	void setDirY(int _dirY) { dirY = _dirY; }

	// draw and erase functions
	virtual void draw() const { draw(ch); }
	virtual void erase() {
		setLastPoint();
		draw(lastPoint);
	}

	
	// movement functions
	virtual void changeDir(Direction dir);
	virtual void move() = 0;
	
	// state update functions
	virtual void resetLocation(int start_x, int start_y) { x = start_x; y = start_y; }
	virtual void activation(bool b) { active = b; };
	virtual bool checkEncounters(Mario& mario);
	void setLastPoint() { lastPoint = pBoard->getChar(x, y); }
	void setBoard(Board& board) { pBoard = &board; }
	bool checkActivationStatus() const { return active; }
	Board& getBoard() const { return *pBoard; }
	int getDirectionRandomly() const;
	void setEncountered(bool b) { encountered = b; } 
	bool isEncountered() { return encountered; } 
	virtual bool reachedBottom();

	// animation functions
	void printAnimation (const char* upper, const char* under, int sleep = 100);
	void eraseAnimation(const char* upper, const char* under);
	virtual void reset(Board& board) = 0; //should be virtual, need to implement in barrel and spec ghosts
	virtual void deactivation() = 0;
	virtual bool getExploding() { return exploding; }
	virtual void setExploding(bool b) { exploding = b; }
};

