#pragma once

class Point
{
	int x;
	int y;
	char ch;


public:
	Point(int _x, int _y, char _c) : x(_x), y(_y), ch(_c) {}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	char getChar() const {
		return ch;
	}
	void setX(int newX) {
		x = newX;
	}
	void setY(int newY) {
		y = newY;
	}
	void setChar(char newChar) {
		ch = newChar;
	}
};


