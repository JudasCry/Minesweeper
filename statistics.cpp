#include "statistics.hpp"

Statistics::Statistics(int totalGames, int wins, int losses, int totalTimePlayed, int bestTime)

    : totalGames(totalGames),
      wins(wins),
      losses(losses),
      totalTimePlayed(totalTimePlayed),
      bestTime(bestTime)

{

}

void Statistics::addGameResult(bool won, int time) {

    totalGames++;

    if (won) {

        wins++;

        if (bestTime == 0 || time < bestTime) {
            bestTime = time;
        }
    }
    else {
        losses++;
    }

    totalTimePlayed += time;
}

// Геттеры //
double Statistics::getWinRate() const {

    if (totalGames == 0) {
        return 0.0;
    }

    return static_cast<double>(wins) / totalGames * 100.0;
}

int Statistics::getBestTime() const {
    return bestTime;
}

double Statistics::getAverageTime() const {

    if (totalGames == 0) {
        return 0.0;
    }

    return static_cast<double>(totalTimePlayed) / totalGames;
}

int Statistics::getTotalGames() const {
    return totalGames;
}

int Statistics::getWins() const {
    return wins;
}

int Statistics::getLosses() const {
    return losses;
}

int Statistics::getTotalTimePlayed() const {
    return totalTimePlayed;
}

// Сброс статистики //
void Statistics::reset() {

    totalGames = 0;
    wins = 0;
    losses = 0;
    totalTimePlayed = 0;
    bestTime = 0;

}
