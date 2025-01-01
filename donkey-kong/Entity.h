#pragma once
#include "Board.h"

/*
* This class represents an entity in the game. 
* every specific entity will inherit from this class.
*/

class Entity
{
	static constexpr char EMPTY_SPACE = ' ';

	char ch;
	int x;
	int y;

	// add direction enum?
	int dirX = 0;
	int dirY = 0;

	char lastPoint = EMPTY_SPACE; // for printing after player passes through

	Board* pBoard = nullptr;

	

public:
	Entity() = default;
	Entity(int x, int y, Board* pBoard, char ch) : x(x), y(y), pBoard(pBoard), ch(ch) {}

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

	// getX
	virtual int getX() const {
		return x;
	}

	// getY
	virtual int getY() const {
		return y;
	}

	// setX
	void setX(int newX) {
		x = newX;
	}

	// setY
	void setY(int newY) {
		y = newY;
	}

	// getChar
	char getChar() const {
		return ch;
	}

	// draw
	void draw() const { // add colors
		draw(ch);
	}


	// setLastPoint
	void setLastPoint() {
		lastPoint = pBoard->getChar(x, y);
	}

	// erase
	void erase() {
		setLastPoint();
		draw(lastPoint);
	}

	// setBoard
	void setBoard(Board& board) {
		pBoard = &board;
	}
	
	// move?
	// changeDir	
	// update()?

};

