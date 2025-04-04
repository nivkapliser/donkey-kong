#include <iostream>
#include "utils.h"


// This function moves the cursor to the specified position on the console window.
// Taken from the lab code.
void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = x; // Set the X coordinate 
    coord.Y = y; // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}


//This function shows or hides the console cursor.
//Taken from the lab code.
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Function to choose randomley between 0 and 1
int randomZeroOrOne()
{
    return (rand() % 2);
}

// Function to get a random number in arange
int getRandomIntInRange(int biggest)
{
    return (rand() % (biggest + 1));
}

// Function to create a file name
std::string createFileName(std::string filename, std::string sufix)
{
    return (filename + '.' + sufix);
}

// Function to remove the suffix from a string
void removeSuffix(std::string& str, const std::string& suffix) {
    if (str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0) {
        str.erase(str.size() - suffix.size());
    }
}