#pragma once

#include <QString>

class Difficulty
{
private:

    QString name;
    int width;
    int height;
    int mines;

public:

    Difficulty(const QString& name, int width, int height, int mines);

    const QString& getName() const;
    int getWidth() const;
    int getHeight() const;
    int getMines() const;

};
