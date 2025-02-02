#include "SpacialGhost.h"

// Function to move the ghost
void SpacialGhost::move() { 

	setDirectionToMario();
	
	if (isFloorEnd()) {
		changeDir(Direction::STOP);
	}
	
	Board& pBoard = getBoard();
	int x = getX(), y = getY();
	int dirX = getDirX(), dirY = getDirY();

	// need to add climbing ladder
	if (pBoard.isLadder(x, y) || pBoard.isLadder(x, y + 1)) {
		if (pMario->getY() < getY()) {
			// Climbing up
			if (pBoard.isLadder(x, y - 1)) {
				setY(--y);
				return;
			}
			else if (pBoard.isFloor(x, y - 1)) {
				// Climbing last level
				setY(y - 2);
				changeDir(Direction::STOP);
				return;
			}
		}

		else if ((pMario->getY() > getY()) && pBoard.isLadder(x, y + 1)) {
			// Deccending ladder
			setY(++y);
			return;
		}
	}
	
	// first step in climbing down ladder
	if ((pMario->getY() > getY()) &&
		pBoard.isLadder(x, y + 2) &&
		pBoard.isFloor(x, y + 1)) {
		setY(y + 2);
	}
	else {
		setX(x + dirX);
		setY(y + dirY);
	}
}

// Function to erase the spacial ghost
void SpacialGhost::erase() {
	Enemy::erase();
}

// Function to set the spacial ghost direction to mario
void SpacialGhost::setDirectionToMario() {
	
	if (!pMario) changeDir(Direction::STOP);
	else {
		if (pMario->getX() > getX()) {
			changeDir(Direction::RIGHT);
		}
		else if (pMario->getX() < getX()) {
			changeDir(Direction::LEFT);
		}
		else {
			changeDir(Direction::STOP);
		}
	}
}

// Fuction to check if the floor ends
bool SpacialGhost::isFloorEnd() const{

	int x = getX();
	int dirX = getDirX();
	int y = getY();
	int dirY = getDirY();

	if (getBoard().getChar(x + dirX, y + 1) == ' ' ||
		getBoard().getChar(x + dirX, y + dirY) == getBoard().getLetter("WALL") ||
		!getBoard().isValidMove(x + dirX, y + dirY))
		return true;
	return false;
}

// Function to deactivate the special ghost
void SpacialGhost::deactivation() {
	activation(false);
}

// Function to reset the special ghost
void SpacialGhost::reset(Board& board, Mario* pMario) {
	setBoard(board);
}

// Function to explode the special ghost
void SpacialGhost::explode() {
	bool isSilent = getBoard().getSilent();
	if (!isSilent) printAnimation("BUSTED!", "xX@Xx", 700);
	deactivation();
}

// Function to check if the special ghost encounters mario
bool SpacialGhost::checkEncounters(Mario& mario) {
	if (mario.getX() == getX() && mario.getY() == getY())
	{
		setEncountered(true);
		explode();
		setEncountered(false);
		return true;
	}
	return false;
}