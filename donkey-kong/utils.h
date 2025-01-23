#pragma once
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <list>
#include <utility>
#include <fstream>
#include <string>
#include <vector>


/*
* This file contains some useful functions for console applications.
*/

static constexpr int ESC = 27;

void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
int randomZeroOrOne();
int getRandomIntInRange(int biggest);
