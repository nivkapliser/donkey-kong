#include "Mario.h"
#include <algorithm>

// can delete:
// ------------------------------------------------
//bool Mario::isLadderUp() const { // move to board
//    return pBoard->getChar(x, y - 1) == LADDER;
//}
//
//bool Mario::isLadder() const { // move to board
//    return pBoard->getChar(x, y) == LADDER;
//}
//
//bool Mario::isFloor(char ch) const { // move to board
//    return std::any_of(std::begin(FORBIDDEN_CHARS), std::end(FORBIDDEN_CHARS),
//        [ch](char forbidden) { return ch == forbidden; });
//}
//
//bool Mario::isLadderDown() const { // move to board
//    return pBoard->getChar(x, y + 2) == LADDER ||
//        pBoard->getChar(x, y + 1) == LADDER;
//}
//
//bool Mario::gravitation() const { // move to board
//    return pBoard->getChar(x, y + 1) == EMPTY_SPACE;
//}

bool Mario::isValidMove() const { // move to board
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
        //dirX = 0;
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

// built base on the lab code
void Mario::move() {
    // Ladder climbing logic
    if (pBoard->isLadder(x, y) || pBoard->getChar(x, y + 1) == LADDER) {
        if (dirY == -1) {
            // Climbing up
            if (pBoard->getChar(x, y - 1) == LADDER) {
                y--;
                return;
            }
            else if (pBoard->getChar(x, y - 1) == '<' || pBoard->getChar(x, y - 1) == '>' || pBoard->getChar(x, y - 1) == '=') { // in function
               // Climbing last level
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

    //// Handle jumping logic
    //if (dirY == -1 && jumpCounter < 2) {
    //    if (isValidMove()) {
    //        y--;
    //        x += dirX;
    //        jumpCounter++;
    //        return;
    //    }
    //}
    //else if (jumpCounter >= 2) {
    //    jumpCounter = 0;
    //    changeDir(DOWN);
    //}

    int newX = x + dirX;
    int newY = y + dirY;
    bool gravity = false;
    
    // first step in climbing down ladder
    if (dirX == 0 && dirY == 1 &&
        pBoard->getChar(x, y + 2) == LADDER &&
        pBoard->isFloor(pBoard->getChar(x, y + 1))) {
        y += 2;
    }
    else if (!isValidMove()) {
        changeDir(STAY);
    }
    else if (pBoard->gravitation(x, y) && !isJump) { //)pBoard->getChar(x, y + 1) == EMPTY_SPACE) {
        gravity = true;
        y++;
    }
    else if (isJump == 2) {
        x += dirX;
        dirY = 1;
        y += dirY;
        dirY = 0;
        //x += 2 * dirX;
        //y += dirY;
        //dirY = 0;
        isJump = 0;
        //changeDir(STAY);

    }
    else if (isJump == 1) {
        x += dirX;
        y += dirY;
        //dirY = 0;
        isJump = 2;
        //changeDir(STAY);
    }
    else if (dirY == -1 && pBoard->getChar(x, y - 2) == EMPTY_SPACE && !isJump) {
        x += dirX;
        y += dirY;
        //dirY = 0;
        isJump = 1;
        //changeDir(STAY);
    }


    else if (!isValidMove() && pBoard->isLadder(x, y) && !isJump) {
        y -= 2;
    }
    else {
        if (!isJump)
        {
            x = newX;
            y = newY;
        }

    }
    
    //if (dirY == -1)
    //{
    //    gravity = false;
    //    y--;

    //}

    fallCounter = gravity ? ++fallCounter : 0;
}

