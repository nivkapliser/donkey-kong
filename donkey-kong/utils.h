#pragma once
#include <windows.h>
#include <iostream>
#include <cstdlib>

/*
* This file contains some useful functions for console applications.
*/

void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
int randomZeroOrOne();
int getRandomIntInRange(int biggest);
