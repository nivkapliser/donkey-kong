#pragma once

/*
* This class represents the main character of the game - Mario. 
* Mario can move in 4 directions: left, right, up (jump or ladder) and down (fall or ladder).
* Mario need to avoid the barrels and climb the ladders to reach Pauline.
* Mario has 3 lives and can jump 2 lines up.
* Mario can move only on the floor and ladders.
*/

#include <iostream>
#include "utils.h"
#include "Board.h"
#include "Point.h"
#include "MenuGraphics.h"

class Mario
{
	enum Direction { LEFT, UP, RIGHT, DOWN, STAY }; // to set the direction of Mario
	static constexpr int JUMP_HEIGHT = 2; // how many lines can mario jump
	static constexpr char keys[] = { 'a', 'w', 'd', 'x', 's' }; // to set the keys for the directions
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]); // to get the size of the keys array
	static constexpr int START_X = 50;
	static constexpr int START_Y = 23;
	static constexpr int MAX_LIVES = 3;
	static constexpr int MAX_FALL = 5; // max number of lines mario can fall
	
	char ch = '@';
	int x = START_X;
	int y = START_Y;
	int lives;

	Direction currentDirection = STAY; // the default starting direction
	int dirX = 0;
	int dirY = 0;

	char lastPoint;
	int isJump = false; 
	int fallCounter = 0;  // to count the number of lines mario fell
	int jumpCounter = 0; // to count the number of lines mario jumped

	Board* pBoard = nullptr;
	MenuGraphics* menuGraphics;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Mario(MenuGraphics* mg) : menuGraphics(mg), x(START_X), y(START_Y), lastPoint(' '), lives(3) {}

	// Function to reset mario position to the starting point
	void resetMarioPosition() {
		x = START_X;
		y = START_Y;
		dirX = dirY = 0;
	}

	// Function to reset mario lives 
	void resetLives() {
		setLives(MAX_LIVES);
	}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}

	// Function to set the number of mario's lives
	void setLives(int l) { 
		lives = l;
	}

	// Function to get the number of mario's lives
	int getLives() const {
		return lives;
	}

	// Function to get the number of lines mario fell
	int getFallCounter() const {
		return fallCounter;
	}

	void  resetFallCounter() {
		fallCounter = 0;
	}

	// Function to check if mario fell too far (more than 5 lines)
	bool fellTooFar() const {
		return fallCounter >= MAX_FALL;
	}

	// Function to reduce mario lives by 1 and update the lives display
	void downLives() {
		lives--;
		eraseLife();
		drawLife();
	}

	void draw() const {
		menuGraphics->setCurrentColor(menuGraphics->getLightGreen());
		draw(ch);
		menuGraphics->setCurrentColor(menuGraphics->getLightRed());
	}

	void erase() {
		setLastPoint();	
		draw(lastPoint);
	}

	void setBoard(Board& board) {
		pBoard = &board;
	}

	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	void eraseLife() const {
		gotoxy(18, 0);
		std::cout << ' ';
	}

	void drawLife() const {
		gotoxy(18, 0);
		std::cout << lives;	
	}

	
	bool metPauline() const {
		return pBoard->getChar(x, y) == '$'; // change to const char
	}

	bool isOnFloor() const {
		return pBoard->isFloor(x, y + 1);
	}

	void changeDir(Direction dir);
	void move();
	void keyPressed(char key);
	void jump();
	void explode();
};
