#include "difficulty.hpp"
#include <stdexcept>

Difficulty::Difficulty(const QString& name, int width, int height, int mines)
{

    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Высота и ширина должны быть положительными");
    }

    if (mines <= 0 || mines >= width * height) {
        throw std::invalid_argument("Неверное количество мин");
    }

    this->name = name;
    this->width = width;
    this->height = height;
    this->mines = mines;

}

const QString& Difficulty::getName() const {
    return name;
}

int Difficulty::getWidth() const {
    return width;
}

int Difficulty::getHeight() const {
    return height;
}

int Difficulty::getMines() const {
    return mines;
}
