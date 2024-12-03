#include "Mario.h"
#include <algorithm>

// Use constexpr for compile-time constants
namespace {
    constexpr char FORBIDDEN_CHARS[] = { 'Q', '<', '>', '=' };
    constexpr char LADDER = 'H';
    constexpr char EMPTY_SPACE = ' ';
}

bool Mario::isLadderUp() const {
    return pBoard->getChar(x, y - 1) == LADDER;
}

bool Mario::isLadder() const {
    return pBoard->getChar(x, y) == LADDER;
}

bool Mario::isFloor(char ch) const {
    return std::any_of(std::begin(FORBIDDEN_CHARS), std::end(FORBIDDEN_CHARS),
        [ch](char forbidden) { return ch == forbidden; });
}

bool Mario::isLadderDown() const {
    return pBoard->getChar(x, y + 2) == LADDER ||
        pBoard->getChar(x, y + 1) == LADDER;
}

bool Mario::gravitation() const {
    return pBoard->getChar(x, y + 1) == EMPTY_SPACE && !isJump;
}

bool Mario::isValidMove() const {
    char nextChar = pBoard->getChar(x + dirX, y + dirY);
    return std::none_of(std::begin(FORBIDDEN_CHARS), std::end(FORBIDDEN_CHARS),
        [nextChar](char forbidden) { return nextChar == forbidden; });
}

void Mario::changeDir(Direction dir) {
    switch (dir) {
    case LEFT:
        dirY = 0;
        dirX = -1;
        break;
    case UP:
        dirY = -1;
        dirX = 0;
        break;
    case RIGHT:
        dirY = 0;
        dirX = 1;
        break;
    case DOWN:
        dirY = 1;
        dirX = 0;
        break;
    case STAY:
        dirY = 0;
        dirX = 0;
        break;
    }
}

void Mario::keyPressed(char key) {
    for (size_t i = 0; i < numKeys; i++) {
        if (std::tolower(key) == keys[i]) {
            changeDir(static_cast<Direction>(i));
            break;
        }
    }
}

void Mario::move() {
    // Ladder climbing logic - prioritize this
    if (isLadder() || pBoard->getChar(x, y + 1) == LADDER) {
        // Vertical ladder movement takes precedence
        if (dirY == -1) {
            // Climbing up
            if (pBoard->getChar(x, y - 1) == LADDER) {
                y--;
                return;
            }
            else if (pBoard->getChar(x, y - 1) == '<' || pBoard->getChar(x, y - 1) == '>' || pBoard->getChar(x, y - 1) == '=') {
                y -= 2;
                changeDir(STAY);
                return;
            }
        }
        else if (dirY == 1 && pBoard->getChar(x, y + 2) == LADDER) {
            // Climbing down
            y++;
            return;
        }
    }

    // Rest of the existing movement logic
    int newX = x + dirX;
    int newY = y + dirY;
    bool isFallSession = false;

    if (dirX == 0 && dirY == 1 &&
        pBoard->getChar(x, y + 2) == LADDER &&
        isFloor(pBoard->getChar(x, y + 1))) {
        y += 2;
    }
    else if (!isValidMove()) {
        changeDir(STAY);
    }
    else if (pBoard->getChar(x, y + 1) == EMPTY_SPACE) {
        isFallSession = true;
        y++;
    }
    else if (dirX == 0 && dirY == -1 && pBoard->getChar(x, y - 2) == EMPTY_SPACE) {
        x += 2 * dirX;
        y -= 2;
        changeDir(STAY);
    }
    else if (dirX != 0 && dirY == -1) {
        x += 2 * dirX;
        y += dirY;
    }
    else if (!isValidMove() && isLadder()) {
        y -= 2;
    }
    else {
        x = newX;
        y = newY;
    }

    fallCounter = isFallSession ? ++fallCounter : 0;
}