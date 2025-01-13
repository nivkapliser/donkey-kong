#include "Board.h"
#include "Mario.h"
#include "Hammer.h"

// Function to reset the board to its original state
// Based on lab code
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], boardFile[i], MAX_X + 1);	
	}
}

// Function to print the board
void Board::print() const
{	
	system("cls");
	menuGraphics->setCurrentColor(menuGraphics->getLightRed());
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
	printLegend();
}

// Function to check if a move is valid (i.e. not on a forbidden character)
bool Board::isValidMove(int x, int y) const {

	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
		return false;
	}

	char nextChar = getChar(x, y);
	for (auto ch : FORBIDDEN_CHARS) {
		if (nextChar == ch || nextChar == WALL) {
			return false;
		}
	}
	return true;
}

// Function to check if a given position is a floor
bool Board::isFloor(int x, int y) const { 
	char c = getChar(x, y);
	for (auto ch : FORBIDDEN_CHARS) {
		if (c == ch) { 
			return true;
		}
	}
	
	return false;
}

// Function to check if a given position is a ladder
bool Board::isLadder(int x, int y) const {
	return currentBoard[y][x] == LADDER; 
}

// Function to check if a given position is empty space
bool Board::gravitation(int x, int y) const {
	return getChar(x, y + 1) == EMPTY_SPACE; 
}

int Board::readBoard(const std::string& filename, Mario& mario, Hammer& hammer) { // handle not found cases
	int g_ind = 1; // needed?
	int returnVal = 0;
	std::ifstream myFile(filename);
	if (!myFile.is_open()) {
		std::cout << "Error opening file\n";
		return returnVal;
	}

	ghostsX.clear();
	ghostsY.clear();

	std::string line;
	for (int i = 0; i < MAX_Y && std::getline(myFile, line); i++) {
		if (line.length() > MAX_X) {
			line = line.substr(0, MAX_X); // for spaces or something
		}
		std::copy(line.begin(), line.end(), boardFile[i]);
		boardFile[i][line.length()] = '\0'; // Null-terminate the string


		// Scan the line for special characters
		for (int j = 0; j < line.length(); j++) {
			if (line[j] == '@') {
				boardFile[i][j] = ' ';	
				mario.setStartX(j);
				mario.setStartY(i);
				marioX = 1;
			}
			else if (line[j] == 'p') {
				boardFile[i][j] = ' ';
				hammer.setStartX(j);
				hammer.setStartY(i);
			}
			else if (line[j] == '&') { // so we can set the barrels starting position
				donkeyX = j;
				donkeyY = i;
			}
			else if (line[j] == 'x') { // so we can set the ghosts starting position
				boardFile[i][j] = ' ';
				ghostsX.push_back(j);
				ghostsY.push_back(i);
			}
			else if (line[j] == 'L') {
				boardFile[i][j] = ' ';
				legendX = j;
				legendY = i;
			}
		}
	}
	if (ghostsX.size() == 0 || legendX == -1 || donkeyX == -1 || marioX == -1) {
		returnVal = -1;
	}
	else {
		returnVal = 1;
	}

	myFile.close();
	return returnVal;
}