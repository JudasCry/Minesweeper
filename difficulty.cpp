#include "difficulty.hpp"
#include <stdexcept>

Difficulty::Difficulty(const /* QString& */ std::string name, int width, int height, int mines)
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

const /* QString& */ std::string Difficulty::getName() const {
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

bool areEquals(const Difficulty& d1, const Difficulty& d2) {

    return d1.name == d2.name &&
           d1.width == d2.width &&
           d1.height == d2.height &&
           d1.mines == d2.mines;

}

bool operator==(const Difficulty& d1, const Difficulty& d2) {

    return d1.name == d2.name &&
           d1.width == d2.width &&
           d1.height == d2.height &&
           d1.mines == d2.mines;

}

std::string Difficulty::getNameWithDimensions() const {
    return name + " [" + std::to_string(width) + "x" +
           std::to_string(height) + ", mines: " + std::to_string(mines) + "]";
}

bool Difficulty::nameContains(const std::string& substring) const {
    return name.find(substring) != std::string::npos;
}

std::string Difficulty::getUpperName() const {

    std::string upper = name;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return upper;

}
