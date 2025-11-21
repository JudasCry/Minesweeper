#include "gamefield.hpp"

GameField::GameField(const Difficulty& difficulty, MinePlacer& minePlacer)

    : totalMines(0),
      cellsRevealed(0),
      flagsPlaced(0),
      width(difficulty.getWidth()),
      height(difficulty.getHeight())
{

    grid.resize(height); // Создаём 'height' строк
    for (int i = 0; i < height; i++) {
        grid[i].resize(width); // Создаём 'width' столбцов в каждой строке
        for (int j = 0; j < width; j++) {
            grid[i][j] = std::make_unique<Cell>(); // Создаём через make_unique
            grid[i][j]->setCoordinates(j, i); // Устанавливаем координаты клетки
        }
    }

}

GameField::GameField(const GameField& other)

    : totalMines(other.totalMines),
      cellsRevealed(other.cellsRevealed),
      flagsPlaced(other.flagsPlaced),
      width(other.width),
      height(other.height)
{

    grid.resize(height);
    for (int i = 0; i < height; i++) {
        grid[i].resize(width);
        for (int j = 0; j < width; j++) {
            grid[i][j] = std::make_unique<Cell>(*other.grid[i][j]);
        }
    }

}

bool GameField::revealCell(Point p) {

    if (p.getX() < 0 || p.getX() >= width || p.getY() < 0 || p.getY() >= height) {
        return false;
    }

    Cell* cell = grid[p.getY()][p.getX()].get(); // Получаем сырой указатель на Cell

    if (cell->getIsRevealed() || cell->getIsFlagged()) {
        return false;
    }

    cell->setRevealed(true);
    cellsRevealed++;

    if (cell->getIsMine()) {
        return false;
    }
    else {

        if (cell->getAdjacentMines() == 0) {

            // Рекурсивно открываем соседние клетки //
            std::vector<Cell*> neighbours = getNeighbours(p);

            for (size_t i = 0; i < neighbours.size(); ++i) {

                Cell* neighbour = neighbours[i];

                if (neighbour && !neighbour->getIsRevealed() && !neighbour->getIsFlagged()) {
                    revealCell(Point(neighbour->getX(), neighbour->getY()));
                }
            }
        }
        return true;
    }
}

bool GameField::toggleFlag(Point p) {

    if (p.getX() < 0 || p.getX() >= width || p.getY() < 0 || p.getY() >= height) {
        return false;
    }

    Cell* cell = grid[p.getY()][p.getX()].get();

    if (cell->getIsRevealed()) {
        return false;
    }

    if (cell->getIsFlagged()) {

        cell->setFlagged(false);
        flagsPlaced--;

    }
    else {

        cell->setFlagged(true);
        flagsPlaced++;

    }

    return true;
}

// Геттеры //
int GameField::getWidth() const {
    return width;
}

int GameField::getHeight() const {
    return height;
}

Cell* GameField::getCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return nullptr;
    }

    return grid[y][x].get();
}

const Cell* GameField::getCell(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return nullptr;
    }

    return grid[y][x].get();
}

std::vector<Cell*> GameField::getNeighbours(Point p) {

    std::vector<Cell*> neighbours;
    int x = p.getX();
    int y = p.getY();

    // Перебираем все 8 возможных соседей //
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {

            if (dx == 0 && dy == 0) continue; // Пропускаем саму ячейку

            int nx = x + dx;
            int ny = y + dy;

            Cell* neighbourCell = getCell(nx, ny);
            neighbours.push_back(neighbourCell);

        }
    }
    return neighbours;
}

// Сеттеры //
void GameField::setTotalMines(int totalMines) {
    this->totalMines = totalMines;
}

void GameField::countAdjacentMines() {

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            if (grid[y][x]->getIsMine()) continue;

            int mineCount = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {

                    if (dx == 0 && dy == 0) continue;

                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {

                        if (grid[ny][nx]->getIsMine()) {
                            mineCount++;
                        }
                    }
                }
            }
            grid[y][x]->setAdjacentMines(mineCount);
       }
    }
}

bool GameField::checkWin() {
    return cellsRevealed == (width * height - totalMines);
}

void GameField::revealAllMines() {

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            if (grid[y][x]->getIsMine()) {
                grid[y][x]->setRevealed(true);
            }
        }
    }
}

void GameField::resetField() {

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            grid[y][x]->setRevealed(false);
            grid[y][x]->setFlagged(false);

        }
    }

    cellsRevealed = 0;
    flagsPlaced = 0;

}
