#pragma once
class Point
{
	int x;
	int y;
    //CR:un used code
	//char c;//?

public:
	Point(int _x, int _y) : x(_x), y(_y) {}
	

	int getX() const {
		return x;
	}

	int getY() const {
		return y;
	}

	int setX(int _x) {
		x = _x;
	}

	int setY(int _y) {
		y = _y;
	}


};

