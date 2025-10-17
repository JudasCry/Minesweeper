#include "mainwindow.hpp"
#include "game.hpp"

#include <QDebug>

#include <QApplication>

void demonstrateClassUsage() {

    // Статическая инициализация //
    qDebug() << QString::fromUtf8("=== Статическая инициализация ===");

    Difficulty beginner("beginner", 10, 10, 10);
    Settings defaultSettings;
    Statistics gameStatistics(0, 0, 0, 0, 0);

    Game game(beginner, defaultSettings, gameStatistics);

    game.startGame(Point(0, 0));

    // Динамическая инициализация //
    qDebug() << QString::fromUtf8("\n=== Динамическая инициализация ===");

    Difficulty* beginner_2 = new Difficulty("beginner", 10, 10, 10);
    Settings* defaultSettings_2 = new Settings();
    Statistics* gameStatistics_2 = new Statistics(0, 0, 0, 0, 0);

    Game* game_2 = new Game(*beginner_2, *defaultSettings_2, *gameStatistics_2);

    game_2->startGame(Point(1, 1));

    delete game_2;
    delete beginner_2;
    delete defaultSettings_2;
    delete gameStatistics_2;

    // Операторы работы по ссылкам и указателю //
    qDebug() << QString::fromUtf8("\n=== Работа по ссылкам и указателям ===");

    Game& gameRef = game;
    gameRef.startGame(Point(2, 2));

    Game* gamePtr = &game;
    gamePtr->startGame(Point(3, 3));

    // Массив динамических объектов класса //
    qDebug() << QString::fromUtf8("\n=== Массив динамических объектов класса ===");

    int numGames = 3;

    std::vector<Game*> games;

    for (int i = 0; i < numGames; ++i) {

        Difficulty beginner_3("beginner", 11 + i, 11 + i, 11 + i);
        Settings defaultSettings_3;
        Statistics gameStatistics_3(0, 0, 0, 0, 0);

        Game* game_3 = new Game(beginner_3, defaultSettings_3, gameStatistics_3);

        games.push_back(game_3);

    }

    for (size_t i = 0; i < games.size(); ++i) {

        Game* game = games[i];
        game->endGame(true);
        delete game;

    }

    games.clear();

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    demonstrateClassUsage();

    return a.exec();
}
