using System;

namespace Lab3
{
    public class Statistics
    {

        public int TotalGames { get; set; }
        public int Wins { get; set; }
        public int Losses { get; set; }
        public int TotalTimePlayed { get; set; }
        public int BestTime { get; set; }

        public Statistics(int totalGames, int wins, int losses, int totalTimePlayed, int bestTime)
        {

            TotalGames = totalGames;
            Wins = wins;
            Losses = losses;
            TotalTimePlayed = totalTimePlayed;
            BestTime = bestTime;

        }

        public void AddGameResult(bool won, int time)
        {

            TotalGames++;

            if (won)
            {
                Wins++;

                if (BestTime == 0 || time < BestTime)
                {
                    BestTime = time;
                }
            }
            else
            {
                Losses++;
            }

            TotalTimePlayed += time;
        }

        public double WinRate()
        {

            if (TotalGames == 0)
            {
                return 0.0;
            }

            return (double)Wins / TotalGames;

        }

        public double AverageTime()
        {

            if (TotalGames == 0)
            {
                return 0.0;
            }

            return (double)TotalTimePlayed / TotalGames;

        }

        public void Reset()
        {

            TotalGames = 0;
            Wins = 0;
            Losses = 0;
            BestTime = 0;

        }

    }
}
