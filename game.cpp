#include "game.hpp"

Game::Game(const Difficulty& difficulty, const Settings& settings, Statistics& externalStatistics)

    : currentDifficulty(difficulty),
      currentSettings(settings),
      minePlacer(),
      field(difficulty, minePlacer),
      timer(),
      gameStatistics(externalStatistics),
      gameState(GameState::Waiting),
      safeStartPoint(0, 0)

{

}

Game::~Game()
{

}

void Game::startGame(const Point& safeStartPoint) {

    this->gameState = GameState::Running;
    this->safeStartPoint = safeStartPoint;

    int numMinesToPlace = currentDifficulty.getMines();

    minePlacer.placeMines(field, numMinesToPlace, this->safeStartPoint);
    field.countAdjacentMines();

    timer.restart();
    timer.start();

}

void Game::restartGame() {

    this->gameState = GameState::Running;

    field.resetField();

    int numMinesToPlace = currentDifficulty.getMines();

    minePlacer.placeMines(field, numMinesToPlace, this->safeStartPoint);
    field.countAdjacentMines();

    timer.restart();
    timer.start();

}

void Game::endGame(bool won) {

    timer.stop();

    int timePlayed = timer.getElapsedSeconds();
    gameStatistics.addGameResult(won, timePlayed);

    gameState = won ? GameState::Won : GameState::Lost;

    if (!won) {
        field.revealAllMines();
    }

}

void Game::cellClick(Point clickPoint) {

    if (gameState != GameState::Running) {
        return;
    }

    bool revealSuccessful = field.revealCell(clickPoint);

    if (!revealSuccessful) {

        endGame(false);
        return;

    }

    if (field.checkWin()) {

        endGame(true);
        return;

    }
}

void Game::flagToggle(Point flagPoint) {

    if (gameState != GameState::Running) {
        return;
    }

    field.toggleFlag(flagPoint);

    if (field.checkWin()) {

        endGame(true);
        return;

    }
}

const GameField& Game::getGameField() const {
    return field;
}

GameTimer& Game::getTimer() {
    return timer;
}

GameState& Game::getGameState() {
    return gameState;
}

const Difficulty& Game::getCurrentDifficulty() {
    return currentDifficulty;
}

void Game::setCurrentDifficulty(const Difficulty& newDifficulty) {

    this->currentDifficulty = newDifficulty;

    restartGame();
}

const Settings& Game::getCurrentSettings() {
    return currentSettings;
}

Statistics& Game::getStatistics() {
    return gameStatistics;
}
