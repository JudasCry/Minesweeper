using System;

namespace Lab3
{
    public class Statistics
    {

        private int _totalGames;
        private int _wins;
        private int _losses;
        private int _totalTimePlayed;
        private int _bestTime;

        public Statistics(int totalGames, int wins, int losses, int totalTimePlayed, int bestTime)
        {

            _totalGames = totalGames;
            _wins = wins;
            _losses = losses;
            _totalTimePlayed = totalTimePlayed;
            _bestTime = bestTime;

        }

        public int TotalGames 
        { 
            get { return _totalGames; } 
        }

        public int Wins
        {
            get { return _wins; }
        }

        public int Losses
        {
            get { return _losses; }
        }

        public int TotalTimePlayed
        {
            get { return _totalTimePlayed; }
        }

        public int BestTime
        {
            get { return _bestTime; }
        }

        public void AddGameResult(bool won, int time)
        {

            _totalGames++;

            if (won)
            {
                _wins++;

                if (_bestTime == 0 || time <  _bestTime)
                {
                    _bestTime = time;
                }
            }
            else
            {
                _losses++;
            }

            _totalTimePlayed += time;
        }

        public double WinRate()
        {

            if (_totalGames == 0)
            {
                return 0.0;
            }

            return (double)_wins / _totalGames;

        }

        public double AverageTime()
        {

            if (_totalGames == 0)
            {
                return 0.0;
            }

            return (double)_totalTimePlayed / _totalGames;

        }

        public void Reset()
        {

            _totalGames = 0;
            _wins = 0;
            _losses = 0;
            _bestTime = 0;

        }

    }
}
