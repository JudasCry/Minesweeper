#include "mineplacer.hpp"
#include "gamefield.hpp"
#include <chrono>

MinePlacer::MinePlacer() : randomGenerator(std::chrono::system_clock::now().time_since_epoch().count())
{

}

void MinePlacer::placeMines(GameField& field, int mines, Point safePoint) {

    int placedMines = 0;
    int fieldWidth = field.getWidth();
    int fieldHeight = field.getHeight();

    int attempts = 0;
    int maxAttempts = fieldWidth * fieldHeight * 2;

    while (placedMines < mines && attempts < maxAttempts) {

        Point randomPos = getRandomPosition(fieldWidth, fieldHeight);

        if (canPlaceMine(field, randomPos, safePoint)) {

            Cell* cell = field.getCell(randomPos.getX(), randomPos.getY());

            if (cell) {

                cell->setMine(true);
                placedMines++;

            }
        }

        attempts++;
    }

    field.setTotalMines(placedMines);
}

bool MinePlacer::canPlaceMine(const GameField& field, Point point, Point safePoint) const {

    // Проверяем не является ли это безопасной точкой //
    if (point.getX() == safePoint.getX() && point.getY() == safePoint.getY()) {
        return false;
    }

    const Cell* cell = field.getCell(point.getX(), point.getY());

    if (cell && !cell->getIsMine()) {
        return true;
    }

    return false;

}

Point MinePlacer::getRandomPosition(int maxX, int maxY) {

    // Создаём распределение для равномерного получения случайных чисел //
    std::uniform_int_distribution<int> distX(0, maxX - 1);
    std::uniform_int_distribution<int> distY(0, maxY - 1);

    // Генерируем случайные координаты //
    int x = distX(randomGenerator);
    int y = distY(randomGenerator);

    return Point(x, y);

}
