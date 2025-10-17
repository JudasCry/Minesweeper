#ifndef POINT_H
#define POINT_H

class Point
{
private:

    int x;
    int y;

public:

    Point(int x, int y);

    int getX() const;
    int getY() const;

};

#endif // POINT_H
