#pragma once

class Statistics
{

private:

    static const int IN_PROCENTS = 100.0;

private:

    int totalGames;
    int wins;
    int losses;
    int totalTimePlayed;
    int bestTime;

public:

    Statistics(int totalGames, int wins, int losses, int totalTimePlayed, int bestTime);

    void addGameResult(bool won, int time);
    double getWinRate() const;
    int getBestTime() const;
    double getAverageTime() const;
    int getTotalGames() const;
    int getWins() const;
    int getLosses() const;
    int getTotalTimePlayed() const;
    void reset();

};
