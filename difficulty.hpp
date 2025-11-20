#pragma once

#include <QString>

class Difficulty
{
private:

    // QString name;
    std::string name;
    int width;
    int height;
    int mines;

public:

    Difficulty(const /* QString& */ std::string name, int width, int height, int mines);

    const /* QString& */ std::string getName() const;
    int getWidth() const;
    int getHeight() const;
    int getMines() const;

    friend bool areEquals(const Difficulty& d1, const Difficulty& d2);

    friend bool operator==(const Difficulty& d1, const Difficulty& d2);

    std::string getNameWithDimensions() const; // конкатенация
    bool nameContains(const std::string& substring) const;  // поиск
    std::string getUpperName() const;           // преобразование регистра

};
