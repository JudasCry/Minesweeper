#pragma once

#include <ostream>

class Point
{
private:

    int x;
    int y;

public:

    Point(int x, int y);

    int getX() const;
    int getY() const;

    friend std::ostream& operator<<(std::ostream& os, const Point& point);

    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

};
