#pragma once
#include <iostream>
#include "utils.h"
#include "Board.h"
#include "MenuGraphics.h"
#include "Hammer.h"

/*
* This class represents the main character of the game - Mario. 
* Mario can move in 4 directions: left, right, up (jump or ladder) and down (fall or ladder).
* Mario need to avoid the barrels and climb the ladders to reach Pauline.
* Mario has 3 lives and can jump 2 lines up.
* Mario can move only on the floor and ladders.
*/

class Mario
{
	// for directions control
	enum class Direction { LEFT, UP, RIGHT, DOWN, STAY };		
	static constexpr char keys[] = { 'a', 'w', 'd', 'x', 's' }; 
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]); 


	//static constexpr int START_X = 50;
	//static constexpr int START_Y = 23;

	// for mario settings
	static constexpr int MAX_LIVES = 3;
	static constexpr int MAX_FALL = 5;			// max number of lines mario can fall
	static constexpr int JUMP_HEIGHT = 2;		// how many lines can mario jump
	static constexpr int BARREL_POINTS = 200;
	static constexpr int GHOST_POINTS = 125;
	static constexpr int PAULINE_POINTS = 1000;
	
	// mario settings
	char ch = '@';
	int x;
	int y;
	int lives;
	int startX;
	int startY;
	
	Direction currentDirection = Direction::STAY; // the default starting direction
	int dirX = 0;
	int dirY = 0;

	// for mario state control
	char lastPoint;
	int isJump = false; 
	int fallCounter = 0;  // to count the number of lines mario fell
	int jumpCounter = 0;  // to count the number of lines mario jumped
	bool smash = false;
	int score;

	Board* pBoard = nullptr;
	MenuGraphics* menuGraphics;
	Hammer* hammer = nullptr;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Mario(MenuGraphics* mg, Hammer* hm) : menuGraphics(mg), lastPoint(' '), lives(MAX_LIVES), hammer(hm) {}

	// Function to reset mario position to the starting point
	void resetMarioPosition() {
		x = startX;
		y = startY;
		dirX = dirY = 0;
	}

	// some getters and setters
	int getX() const { return x; }
	int getY() const { return y; }
	int getDirX() const { return dirX; }
	void setStartX(int x) { startX = x; }
	void setStartY(int y) { startY = y; }
	void resetLives() { setLives(MAX_LIVES); }
	void setLives(int l) { lives = l; }
	int getLives() const { return lives; }
	void setBoard(Board& board) { pBoard = &board; }
	void setLastPoint() { lastPoint = pBoard->getChar(x, y); }

	// drawing and erasing mario, lives and score
	void draw() const {
		menuGraphics->setCurrentColor(menuGraphics->getLightGreen());
		draw(ch);
		menuGraphics->setCurrentColor(menuGraphics->getLightRed());
	}
	void erase() {
		setLastPoint();
		draw(lastPoint);
	}
	void eraseLife() const {
		gotoxy(18, 0);
		std::cout << ' ';
	}
	void drawLife() const {
		gotoxy(pBoard->getLegendX() + 7, pBoard->getLegendY()); // should be const.. 
		std::cout << lives;
	}
	void drawScore() const {
		gotoxy(pBoard->getLegendX() + 18, pBoard->getLegendY()); // should be const.. 
		std::cout << score;
	}


	// falls control
	int getFallCounter() const { return fallCounter; }
	void resetFallCounter() { fallCounter = 0; }
	bool fellTooFar() const { return fallCounter >= MAX_FALL; }

	// lives and score control
	void downLives() {
		lives--;
		eraseLife();
		drawLife();
	}
	void resetScore() { score = 0; }
	void increaseScore(int increase) { score += increase; }
	int getBarrelPoints() const { return BARREL_POINTS; }
	int getGhostPoints() const { return GHOST_POINTS; }
	int getPaulinePoints() const { return PAULINE_POINTS; }

	// movement control
	void changeDir(Direction dir);
	void move();
	bool keyPressed(char key);
	void jump();
	void explode();
	void ghosted();
	bool isOnFloor() const { return (pBoard->isFloor(x, y + 1) || pBoard->isBoarder(x, y + 1)); }
	bool metPauline() const { return pBoard->getChar(x, y) == '$'; }	
	
	// hammer control
	bool getSmash() const { return smash; }
	void setSmash(bool s) { smash = s; }
	void checkIfMetHammer();
	void setHammer(Hammer* h) { hammer = h; }
	Hammer* getHammer() const { return hammer; }
	void smashOnce() { smash = false; }
	void smashEnemies();
};
