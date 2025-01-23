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

// Function to print the legend
void Board::printLegend() const {
	gotoxy(legendX, legendY);
	std::cout << "Lives: " << " | Score: " << std::endl;
	gotoxy(legendX, legendY + 1);
	std::cout << "Hammer: ";
}

// Function to check if a given position is a boarder
bool Board::isBoarder(int x, int y) const {
	if (getChar(x, y) == WALL || y >= MAX_Y)
		return true;
	return false;
}

// Function to print the board
void Board::print() const {	
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

/* Function to read the selected board from file.
* The function returns:
* 0 - could not open the file
* 1 - success reading board
* -1 - missing objects when reading the board.
* The function pads with spaces if board too small. 
* if more than one mario or donkey kong in the file, it will take the last position it read
*/
int Board::readBoard(const std::string& filename, Mario& mario, Hammer& hammer) { 
	int returnVal = 1;
	int valid = 0;
	int i = 0;
	std::ifstream myFile(filename);
	if (!myFile.is_open()) {
		std::cout << "Error opening file\n";
		return returnVal;
	}

	// Reset the ghost positions
	ghostsX.clear();
	ghostsY.clear();

	std::string line;
	for (; i < MAX_Y && std::getline(myFile, line); i++) {

		// resize the line if it is too long
		if (line.length() > MAX_X) {
			line = line.substr(0, MAX_X); 
		}
		// to pad with spaces if the line is too short
		else if (line.length() < MAX_X) {
			line.resize(MAX_X, ' '); 
		}

		// copy the line to the boardFile
		std::copy(line.begin(), line.end(), boardFile[i]);
		boardFile[i][line.length()] = '\0'; 

		// scan the line for special characters - for setting the start positions
		valid = setStartPositions(line, mario, hammer, i);
		if (valid == -1)
			return valid;
	}

	// pad with empty lines if the number of lines is smaller than MAX_Y
	for (; i < MAX_Y; i++) {
		std::fill(boardFile[i], boardFile[i] + MAX_X, ' ');
		boardFile[i][MAX_X] = '\0'; // Null-terminate the string
	}

	for (int i : set_table) //checks that every mandatory char is in board
	{
		if (i != 1)
			returnVal =  -1;
	}
	std::memset(set_table, 0, sizeof(set_table)); //reset the set table, for the next reading

	curr_board_name = filename;
	removeSuffix(curr_board_name, ".screen");

	myFile.close();
	return returnVal;
}

// Function to get the start positions of the entities and to check if all the mandatory objects are in the board
int Board::setStartPositions(std::string line, Mario& mario, Hammer& hammer, int i) {

	for (int j = 0; j < line.length(); j++) {
		// check for entities and set their starting positions
		if (line[j] == '@') {
			if (j == 0 || set_table[MARIO] == 1) // there is only one mario in the game
				return -1;

			boardFile[i][j] = ' ';
			mario.setStartX(j);
			mario.setStartY(i);
			set_table[MARIO] = 1;
		}
		else if (line[j] == 'p') {
			if (j == 0 || set_table[HAMMER] == 1) //there is only one hammer in the game
				return -1;
			boardFile[i][j] = ' ';
			hammer.setStartX(j);
			hammer.setStartY(i);
			set_table[HAMMER] = 1;
		}
		else if (line[j] == '&') { // so we can set the barrels starting position
			if (j == 0 || set_table[DONKEY] == 1)  //there is only one donkey in the game
				return -1;
			donkeyX = j;
			donkeyY = i;
			set_table[DONKEY] = 1;
		}
		else if (line[j] == 'x') {
			if (j == 0)
				return -1;
			boardFile[i][j] = ' ';
			ghostsX.push_back(j);
			ghostsY.push_back(i);
			set_table[GHOST] = 1;
		}
		else if (line[j] == 'L') {
			if (set_table[LEGEND] == 1)
				return -1;
			boardFile[i][j] = ' ';
			legendX = j;
			legendY = i;
			set_table[LEGEND] = 1;
		}
		//checks if the mandatory chars are in the board
		else if (line[j] == PAULINE) {
			if (set_table[PAULI] == 1)
				return -1;
			set_table[PAULI] = 1;
		}
		else if (line[j] == LADDER) { set_table[LADD] = 1; }
		else if (line[j] == FLOOR[0]) { set_table[FL0] = 1; }
		else if (line[j] == FLOOR[1]) { set_table[FL1] = 1; } 
		else if (line[j] == FLOOR[2]) { set_table[FL2] = 1; }
		else if (line[j] != WALL && line[j] != EMPTY_SPACE) //checks if it not a mandatory char that allowed to be in game.
			return -1;
	}
}

// Function to get the letter of the object
char Board::getLetter(const char* object)
{
	if (object == "WALL")
		return WALL;
	else if (object == "LADDER")
		return LADDER;
	else if (object == "PAULINE")
		return PAULINE;
}