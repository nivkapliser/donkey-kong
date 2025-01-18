#include "Board.h"
#include "Mario.h"
#include "Hammer.h"
#include <algorithm>

// Function to reset the board to its original state
// Based on lab code
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], boardFile[i], MAX_X + 1);	
	}
}

void Board::printLegend() const {
	gotoxy(legendX, legendY);
	std::cout << "Lives: " << " | Score: " << std::endl;
	gotoxy(legendX, legendY + 1);
	std::cout << "Hammer: ";
}

bool Board::isBoarder(int x, int y) const {
	if (getChar(x, y) == WALL || y >= MAX_Y)
		return true;
	return false;
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
	for (auto ch : FLOOR) {
		if (nextChar == ch || nextChar == WALL) {
			return false;
		}
	}
	return true;
}

// Function to check if a given position is a floor
bool Board::isFloor(int x, int y) const { 
	char c = getChar(x, y);
	for (auto ch : FLOOR) {
		if (c == ch) { 
			return true;
		}
	}
	return false;
}

// Function to check if a given position is empty space
bool Board::gravitation(int x, int y, int dirX) const {
	if (getChar(x + dirX, y + 1) == EMPTY_SPACE)
		return true;
	return false;
}

// Function to read the selected board from file. 
// The function returns:
// 0 - could not open the file
// 1 - success reading board
// -1 - missing objects when reading the board.
// The function pads with spaces if board too small. 
// if more than one mario or donkey kong in the file, it will take the last position it read
int Board::readBoard(const std::string& filename, Mario& mario, Hammer& hammer) { 
	int g_ind = 1; // needed?
	int returnVal = 0;
	int i = 0;
	std::ifstream myFile(filename);
	if (!myFile.is_open()) {
		std::cout << "Error opening file\n";
		return returnVal;
	}

	ghostsX.clear();
	ghostsY.clear();

	std::string line;
	for (; i < MAX_Y && std::getline(myFile, line); i++) {

		if (line.length() > MAX_X) {
			line = line.substr(0, MAX_X); 
		}
		else if (line.length() < MAX_X) {
			line.resize(MAX_X, ' '); // to pad with spaces
		}

		std::copy(line.begin(), line.end(), boardFile[i]);
		boardFile[i][line.length()] = '\0'; // Null-terminate the string


		// Scan the line for special characters
		setStartPositions(line, mario, hammer, i);
	}

	// Pad with empty lines if the number of lines is smaller than MAX_Y
	for (; i < MAX_Y; i++) {
		std::fill(boardFile[i], boardFile[i] + MAX_X, ' ');
		boardFile[i][MAX_X] = '\0'; // Null-terminate the string
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

void Board::setStartPositions(std::string line, Mario& mario, Hammer& hammer, int i) {

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
		else if (line[j] == 'x') { 
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

char Board::getLetter(const char* object)
{
	if (object == "WALL")
		return WALL;
	else if (object == "LADDER")
		return LADDER;
	else if (object == "PAULINE")
		return PAULINE;
}