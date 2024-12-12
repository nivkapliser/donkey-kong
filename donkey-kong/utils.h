#pragma once
/*
* This file contains some useful functions for console applications.
*/
#include <windows.h>
#include <cstdlib>

enum COLORS {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GRAY = 7,
    DARK_GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

void gotoxy(int x, int y);
void color(int color);
void ShowConsoleCursor(bool showFlag);
