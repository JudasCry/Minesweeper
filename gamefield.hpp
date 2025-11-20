#pragma once

#include "cell.hpp"
#include "mineplacer.hpp"
#include "difficulty.hpp"
#include "point.hpp"
#include <vector>

class GameField
{
private:

    std::vector<std::vector<std::unique_ptr<Cell>>> grid;
    int totalMines;
    int cellsRevealed;
    int flagsPlaced;
    int width;
    int height;

public:

    GameField(const Difficulty& difficulty, MinePlacer& minePlacer);

    GameField(const GameField& other);

    bool revealCell(Point p);
    bool toggleFlag(Point p);
    Cell* getCell(int x, int y);
    const Cell* getCell(int x, int y) const;
    std::vector<Cell*> getNeighbours(Point p);
    int getWidth() const;
    int getHeight() const;
    void setTotalMines(int totalMines);
    void countAdjacentMines();
    bool checkWin();
    void revealAllMines();
    void resetField();

};
