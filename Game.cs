using System;

namespace Lab3
{
    public class Game
    {

        private readonly MinePlacer _minePlacer;
        private Point _safeStartPoint;

        public GameField Field { get; }
        public GameTimer Timer { get; }
        public Difficulty CurrentDifficulty { get; set; }
        public GameState State { get; private set; }
        public Settings CurrentSettings { get; }
        public Statistics GameStatistics { get; }

        public event Action<bool> GameEnded; // Событие, вызываемое при окончании игры

        public Game(Difficulty difficulty, Settings settings, Statistics externalStatistics)
        {

            CurrentDifficulty = difficulty;
            CurrentSettings = settings;
            _minePlacer = new MinePlacer();
            Field = new GameField(CurrentDifficulty, _minePlacer);
            Timer = new GameTimer();
            GameStatistics = externalStatistics;
            State = GameState.Waiting;
            _safeStartPoint = new Point(0, 0);

        }

        public void StartGame(Point safeStartPoint)
        {

            State = GameState.Running;
            _safeStartPoint = safeStartPoint;

            int numMinesToPlace = CurrentDifficulty.Mines;

            // Расставляем мины и считаем соседние мины //
            _minePlacer.PlaceMines(Field, numMinesToPlace, _safeStartPoint);
            Field.CountAdjacentMines();

            // Перезапускаем и запускаем таймер //
            Timer.Restart();
            Timer.Start();

        }

        public void RestartGame()
        {

            State = GameState.Running;

            Field.ResetField(); // Сбрасываем поле

            int numMinesToPlace = CurrentDifficulty.Mines;

            // Перестанавливаем мины и считаем соседние //
            _minePlacer.PlaceMines(Field, numMinesToPlace, _safeStartPoint);
            Field.CountAdjacentMines();

            Timer.Restart();
            Timer.Start();

        }

        public void EndGame(bool won)
        {

            Timer.Stop();

            int timePlayed = Timer.ElapsedSeconds;

            // Добавляем результат в статистику //
            GameStatistics.AddGameResult(won, timePlayed);

            State = won ? GameState.Won : GameState.Lost;

            if (!won)
            {
                Field.RevealAllMines();
            }

            // Вызываем событие GameEnded, чтобы UI отреагировал //
            GameEnded?.Invoke(won);
        }

        public void CellClick(Point clickPoint)
        {

            if (State != GameState.Running)
            {
                return;
            }

            bool revealSuccessful = Field.RevealCell(clickPoint);

            if (!revealSuccessful)
            {

                Cell clickedCell = Field.GetCell(clickPoint.X, clickPoint.Y);
                if (clickedCell != null && clickedCell.IsMine)
                {
                    EndGame(false);
                }

                return;
            }

            if (Field.CheckWin())
            {

                EndGame(true);
                return;

            }

        }

        public void FlagToggle(Point flagPoint)
        {

            if (State != GameState.Running)
            {
                return;
            }

            Field.ToggleFlag(flagPoint);

            if (Field.CheckWin())
            {
                EndGame(true);
                return;
            }

        }

        public void SetCurrentDifficulty(Difficulty newDifficulty)
        {

            CurrentDifficulty = newDifficulty;
            RestartGame();

        }
        
    }
}
