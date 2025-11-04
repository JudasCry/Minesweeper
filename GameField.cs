using System.Collections.Generic;

namespace Lab3
{
    public class GameField
    {

        private Cell[,] _grid;
        private int _totalMines;
        private int _cellsRevealed;
        private int _flagsPlaced;
        private readonly int _width;
        private readonly int _height;

        public GameField(Difficulty difficulty, MinePlacer minePlacer)
        {

            _width = difficulty.Width;
            _height = difficulty.Height;

            _grid = new Cell[_height, _width]; // Создаём двумерный массив

            for (int y = 0; y < _height; y++)
            {
                for (int x = 0; x < _width; x++)
                {
                    _grid[y, x] = new Cell(); // Создаём клетку
                    _grid[y, x].SetCoordinates(x, y); // Устанавливаем координаты клетки
                }

            }

        }

        public int Width
        {
            get { return _width; }
        }

        public int Height
        {
            get { return _height; }
        }

        public int TotalMines
        {
            set { _totalMines = value; }
        }

        public bool RevealCell(Point p)
        {

            if (p.X < 0 || p.X >= _width || p.Y < 0 || p.Y >= _height)
            {
                return false;
            }

            Cell cell = GetCell(p.X, p.Y);

            if (cell == null || cell.IsRevealed || cell.IsFlagged)
            {
                return false;
            }

            cell.IsRevealed = true;
            _cellsRevealed++;

            if (cell.IsMine)
            {
                return false;
            }
            else
            {
                if (cell.AdjacentMines == 0)
                {

                    // Рекурсивно открываем соседние клетки //
                    List<Cell> neighbours = GetNeighbours(p);

                    foreach (Cell neighbour in neighbours)
                    {
                        if (neighbour != null && !neighbour.IsRevealed && !neighbour.IsFlagged)
                        {
                            RevealCell(new Point(neighbour.X, neighbour.Y));
                        }
                    }

                    return true;
                }
            }

            return true;

        }

        public List<Cell> GetNeighbours(Point p)
        {

            List<Cell> neighbours = new List<Cell>();

            int x = p.X;
            int y = p.Y;

            // Перебираем все 8 возможных соседей //
            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {

                    if (dx == 0 && dy == 0) continue; // Пропускаем саму клетку

                    int nx = x + dx;
                    int ny = y + dy;

                    Cell neighbourCell = GetCell(nx, ny);

                    if (neighbourCell != null)
                    {
                        neighbours.Add(neighbourCell);
                    }

                }
            }

            return neighbours;

        }

        public void SetTotalMines(int totalMines)
        {
            _totalMines = totalMines;
        }

        public void CountAdjacentMines()
        {

            for (int y = 0; y < _height; ++y)
            {
                for (int x = 0; x < _width; ++x)
                {

                    if (_grid[y, x].IsMine) continue;

                    int mineCount = 0;

                    for (int dy = -1; dy <= 1; ++dy)
                    {
                        for (int dx = -1; dx <= 1; ++dx)
                        {

                            if (dx == 0 && dy == 0) continue;

                            int nx = x + dx;   
                            int ny = y + dy;

                            if (nx >= 0 && nx < _width && ny >= 0 && ny < _height)
                            {
                                if (_grid[ny, nx].IsMine)
                                {
                                    mineCount++;
                                }
                            }

                        }
                    }
                    _grid[y, x].AdjacentMines = mineCount;
                }
            }
        }

        public bool ToggleFlag(Point p)
        {

            if (p.X < 0 || p.X >= _width || p.Y < 0 || p.Y >= _height)
            {
                return false;
            }

            Cell cell = GetCell(p.X, p.Y);

            if (cell == null || cell.IsRevealed)
            {
                return false;
            }

            if (cell.IsFlagged)
            {
                cell.IsFlagged = false;
                _flagsPlaced--;
            }
            else
            {
                cell.IsFlagged = true;
                _flagsPlaced++;
            }

            return true;

        }

        public Cell GetCell(int x, int y)
        {
            
            if (x < 0 || x >= _width || y < 0 || y >= _height)
            {
                return null;
            }

            return _grid[y, x];

        }

        public bool CheckWin()
        {
            return _cellsRevealed == (_width * _height - _totalMines);
        }

        public void RevealAllMines()
        {

            for (int y = 0; y < _height; ++y)
            {
                for (int x = 0; x < _width; ++x)
                {
                    if (_grid[y, x].IsMine)
                    {
                        _grid[y, x].IsRevealed = true;
                    }
                }
            }

        }

        public void ResetField()
        {

            for (int y = 0; y < _height; ++y)
            {
                for (int x = 0; x < _width; ++x)
                {
                    _grid[y, x].IsRevealed = false;
                    _grid[y, x].IsFlagged = false;
                }
            }

            _cellsRevealed = 0;
            _flagsPlaced = 0;

        }

    }
}
