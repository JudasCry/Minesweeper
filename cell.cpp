#include "cell.hpp"

Cell::Cell() : isMine(false), isRevealed(false), isFlagged(false), adjacentMines(0), x(-1), y(-1)
{

}

void Cell::reset() {

    isMine = false;
    isRevealed = false;
    isFlagged = false;
    adjacentMines = 0;
    x = -1;
    y = -1;

}

void Cell::setMine(bool mine) {
    isMine = mine;
}

void Cell::setRevealed(bool revealed) {
    isRevealed = revealed;
}

void Cell::setFlagged(bool flagged) {
    isFlagged = flagged;
}

void Cell::setAdjacentMines(int count) {
    adjacentMines = count;
}

void Cell::setCoordinates(int x, int y) {

    this->x = x;
    this->y = y;

}

bool Cell::getIsMine() const {
    return isMine;
}

bool Cell::getIsRevealed() const {
    return isRevealed;
}

bool Cell::getIsFlagged() const {
    return isFlagged;
}

int Cell::getAdjacentMines() const {
    return adjacentMines;
}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

bool Cell::isEmpty() const {
    return !isMine && !isFlagged;
}
