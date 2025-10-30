#pragma once

#include <random>
#include "point.hpp"

class GameField;

class MinePlacer
{
private:

    std::mt19937 randomGenerator;

public:

    MinePlacer();

    void placeMines(GameField& field, int mines, Point safePoint);
    bool canPlaceMine(const GameField& field, Point point, Point safePoint) const;
    Point getRandomPosition(int maxX, int maxY);

};
