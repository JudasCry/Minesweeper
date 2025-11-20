#include "point.hpp"

Point::Point(int x, int y) : x(x), y(y)
{

}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {

    os << "(" << point.x << ", " << point.y << ")";
    return os;

}

Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return x != other.x && y != other.y;
}
