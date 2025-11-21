#pragma once

#include "gamefield.hpp"
#include "gametimer.hpp"
#include "mineplacer.hpp"
#include "difficulty.hpp"
#include "settings.hpp"
#include "statistics.hpp"
#include "point.hpp"
#include "gamestate.hpp"

class Game
{
private:

    MinePlacer minePlacer;
    GameField field;
    GameTimer timer;
    Difficulty currentDifficulty;
    GameState gameState;
    Settings currentSettings;
    std::shared_ptr<Statistics> gameStatistics;
    Point safeStartPoint;

public:

    Game(const Difficulty& difficulty, const Settings& settings, std::shared_ptr<Statistics> statistics);
    ~Game();

    void startGame(const Point& safeStartPoint);
    void restartGame();
    void endGame(bool won);
    void cellClick(Point clickPoint);
    void flagToggle(Point flagPoint);
    const GameField& getGameField() const;
    GameTimer& getTimer();
    GameState& getGameState();
    const Difficulty& getCurrentDifficulty();
    void setCurrentDifficulty(const Difficulty& newDifficulty);
    const Settings& getCurrentSettings();
    std::shared_ptr<Statistics> getStatistics();

};
