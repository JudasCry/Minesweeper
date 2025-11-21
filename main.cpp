#include "mainwindow.hpp"
#include "game.hpp"

#include <QDebug>

#include <QApplication>

void demonstrateClassUsage() {

    // Статическая инициализация //
    qDebug() << "=== СТАТИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ===";

    Difficulty beginner("beginner", 10, 10, 10);
    qDebug() << "Создан уровень:" << beginner.getName()
             << beginner.getWidth() << "x" << beginner.getHeight()
             << "с" << beginner.getMines() << "минами";

    Settings defaultSettings;
    qDebug() << "Настройки: язык" << defaultSettings.getLanguage()
             << "звук" << (defaultSettings.getSoundEnabled() ? "вкл" : "выкл");

    std::shared_ptr<Statistics> gameStatistics = std::make_shared<Statistics>(0, 0, 0, 0, 0);
    qDebug() << "Статистика: игр" << gameStatistics->getTotalGames()
             << "побед" << gameStatistics->getWins();

    Game game(beginner, defaultSettings, gameStatistics);
    qDebug() << "Игра создана успешно!";

    game.startGame(Point(0, 0));
    qDebug() << "Игра запущена с безопасной точкой (0, 0)";

    qDebug() << "Таймер работает:" << game.getTimer().getIsRunning();

    // Динамическая инициализация //
    qDebug() << "\n=== ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ===";

    std::unique_ptr<Difficulty> beginner_2 = std::make_unique<Difficulty>("beginner", 10, 10, 10);
    std::unique_ptr<Settings> defaultSettings_2 = std::make_unique<Settings>();
    std::shared_ptr<Statistics> gameStatistics_2 = std::make_shared<Statistics>(0, 0, 0, 0, 0);

    qDebug() << "Уровень:" << beginner_2->getName();
    qDebug() << "Статистика: побед" << gameStatistics_2->getWins()
             << "процент побед" << gameStatistics_2->getWinRate() << "%";

    std::unique_ptr<Game> game_2 = std::make_unique<Game>(*beginner_2, *defaultSettings_2, gameStatistics_2);

    game_2->startGame(Point(1, 1));
    qDebug() << "Динамическая игра запущена!";

    qDebug() << "Память освобождена самостоятельно умными указателями";

    // Операторы работы по ссылкам и указателю //
    qDebug() << "\n=== РАБОТА ПО ССЫЛКАМ И УКАЗАТЕЛЯМ ===";

    Game& gameRef = game;
    qDebug() << "Создана ссылка на существующую игру";

    gameRef.startGame(Point(2, 2));
    qDebug() << "Запускаем игру через ссылку с безопасной точкой (2, 2)";

    qDebug() << "Состояние игры через ссылку:"
             << (gameRef.getGameState() == GameState::Running ? "Running" :
             gameRef.getGameState() == GameState::Waiting ? "Waiting" : "Other");

    qDebug() << "Таймер через ссылку работает:"
             << gameRef.getTimer().getIsRunning();

    qDebug() << "Уровень сложности через ссылку:"
             << gameRef.getCurrentDifficulty().getName();

    Game* gamePtr = &game;
    qDebug() << "Создан указатель на существующую игру";

    gamePtr->startGame(Point(3, 3));
    qDebug() << "Запускаем игру через указатель с безопасной точкой (3, 3)";

    qDebug() << "Состояние игры через указатель:"
             << (gamePtr->getGameState() == GameState::Running ? "Running" :
             gamePtr->getGameState() == GameState::Waiting ? "Waiting" : "Other");

    qDebug() << "Размер поля через указатель:"
             << gamePtr->getGameField().getWidth() << "x" << gamePtr->getGameField().getHeight();

    qDebug() << "Таймер через указатель:"
             << gamePtr->getTimer().getFormattedTime();

    // Массив динамических объектов класса //
    qDebug() << "\n=== МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ КЛАССА ===";

    int numGames = 3;

    std::vector<std::unique_ptr<Game>> games;
    qDebug() << "Создаем массив из" << numGames << "динамических игр";

    for (int i = 0; i < numGames; ++i) {
        qDebug() << "--- Создание игры" << (i + 1) << "---";

        Difficulty beginner_3("beginner", 11 + i, 11 + i, 11 + i);
        qDebug() << "Уровень сложности:" << beginner_3.getName()
                 << beginner_3.getWidth() << "x" << beginner_3.getHeight()
                 << "с" << beginner_3.getMines() << "минами";

        Settings defaultSettings_3;
        std::shared_ptr<Statistics> gameStatistics_3 = std::make_shared<Statistics>(0, 0, 0, 0, 0);

        std::unique_ptr<Game> game_3 = std::make_unique<Game>(beginner_3, defaultSettings_3, gameStatistics_3);
        qDebug() << "Динамическая игра создана, адрес:" << game_3.get();

        game_3->startGame(Point(i, i));
        qDebug() << "Игра запущена с безопасной точкой (" << i << "," << i << ")";
        qDebug() << "Состояние:" <<
                 (game_3->getGameState() == GameState::Running ? "Running" : "Waiting");
        qDebug() << "Таймер работает:" << game_3->getTimer().getIsRunning();

        games.push_back(std::move(game_3));
        qDebug() << "Игра добавлена в массив. Размер массива:" << games.size();

    }

    qDebug() << "Удаляем массив из" << numGames << "динамических игр";

    for (size_t i = 0; i < games.size(); ++i) {
        qDebug() << "--- Завершение игры" << (i + 1) << "---";

        std::unique_ptr<Game>& currentGame = games[i];
        qDebug() << "Адрес игры:" << currentGame.get();
        qDebug() << "Уровень:" << currentGame->getCurrentDifficulty().getName();
        qDebug() << "Размер поля:" << currentGame->getGameField().getWidth()
                 << "x" << currentGame->getGameField().getHeight();

        currentGame->endGame(true);
        qDebug() << "Завершаем игру как выигранную";

        qDebug() << "Игра удалена автоматически умным указателем";

    }

    games.clear();
    qDebug() << "\nМассив очищен. Размер массива:" << games.size();
    qDebug() << "Все динамические игры успешно созданы и уничтожены!";

    // Динамический массив объектов класса //
    qDebug() << "\n=== ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ КЛАССА ===";

    std::vector<std::unique_ptr<Game>> gamesArray;

    for (int i = 0; i < numGames; ++i) {
        qDebug() << "--- Создание элемента массива" << i << "---";

        Difficulty difficulty("Beginner", 10 + i, 10 + i, 5 + i);

        gamesArray.push_back(std::make_unique<Game>(difficulty, Settings(), gameStatistics));
        qDebug() << "Создан объект Game, адрес в массиве:" << gamesArray[i].get();

        gamesArray[i]->startGame(Point(i, i));
        qDebug() << "Игра запущена с безопасной точкой (" << i << "," << i << ")";

        gamesArray[i]->endGame(true);
        qDebug() << "Завершаем игру как выигранную";

        qDebug() << "Статистика после игры" << i << ":"
                 << gameStatistics->getTotalGames() << "игр";
    }

    qDebug() << "\n--- Автоматическое удаление динамического массива ---";

    qDebug() << "Динамический массив полностью удален умными указателями!";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    demonstrateClassUsage();

    return a.exec();
}
