using System;

namespace Lab3
{
    public class Game
    {

        private readonly MinePlacer _minePlacer;
        private readonly GameField _field;
        private readonly GameTimer _timer;

        private Difficulty _currentDifficulty;
        private GameState _state;
        private Settings _currentSettings;
        private Statistics _gameStatistics;
        private Point _safeStartPoint;

        public event Action<bool> GameEnded; // Событие, вызываемое при окончании игры

        public Game(Difficulty difficulty, Settings settings, Statistics externalStatistics)
        {

            _currentDifficulty = difficulty;
            _currentSettings = settings;
            _minePlacer = new MinePlacer();
            _field = new GameField(_currentDifficulty, _minePlacer);
            _timer = new GameTimer();
            _gameStatistics = externalStatistics;
            _state = GameState.Waiting;
            _safeStartPoint = new Point(0, 0);

        }

        public GameField Field
        {
            get { return _field; }
        }

        public GameTimer Timer
        {
            get { return _timer; }
        }

        public GameState State
        {
            get { return _state; }
        }

        public Difficulty CurrentDifficulty
        {
            get { return _currentDifficulty; }
        }

        public Settings CurrentSettings
        {
            get { return  _currentSettings; }
        }

        public Statistics GameStatistics
        {
            get { return _gameStatistics; }
        }

        public void StartGame(Point safeStartPoint)
        {

            _state = GameState.Running;
            _safeStartPoint = safeStartPoint;

            int numMinesToPlace = _currentDifficulty.Mines;

            // Расставляем мины и считаем соседние мины //
            _minePlacer.PlaceMines(_field, numMinesToPlace, _safeStartPoint);
            _field.CountAdjacentMines();

            // Перезапускаем и запускаем таймер //
            _timer.Restart();
            _timer.Start();

        }

        public void RestartGame()
        {

            _state = GameState.Running;

            _field.ResetField(); // Сбрасываем поле

            int numMinesToPlace = _currentDifficulty.Mines;

            // Перестанавливаем мины и считаем соседние //
            _minePlacer.PlaceMines(_field, numMinesToPlace, _safeStartPoint);
            _field.CountAdjacentMines();

            _timer.Restart();
            _timer.Start();

        }

        public void EndGame(bool won)
        {

            _timer.Stop();

            int timePlayed = _timer.ElapsedSeconds;

            // Добавляем результат в статистику //
            _gameStatistics.AddGameResult(won, timePlayed);

            _state = won ? GameState.Won : GameState.Lost;

            if (!won)
            {
                _field.RevealAllMines();
            }

            // Вызываем событие GameEnded, чтобы UI отреагировал //
            GameEnded?.Invoke(won);
        }

        public void CellClick(Point clickPoint)
        {

            if (_state != GameState.Running)
            {
                return;
            }

            bool revealSuccessful = _field.RevealCell(clickPoint);

            if (!revealSuccessful)
            {

                Cell clickedCell = _field.GetCell(clickPoint.X, clickPoint.Y);
                if (clickedCell != null && clickedCell.IsMine)
                {
                    EndGame(false);
                }

                return;
            }

            if (_field.CheckWin())
            {

                EndGame(true);
                return;

            }

        }

        public void FlagToggle(Point flagPoint)
        {

            if (_state != GameState.Running)
            {
                return;
            }

            _field.ToggleFlag(flagPoint);

            if (_field.CheckWin())
            {
                EndGame(true);
                return;
            }

        }

        public void SetCurrentDifficulty(Difficulty newDifficulty)
        {

            _currentDifficulty = newDifficulty;
            RestartGame();

        }
        
    }
}
